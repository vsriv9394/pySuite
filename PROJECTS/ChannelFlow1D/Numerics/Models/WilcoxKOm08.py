from pyad.pyAD import *
from .Laminar import LaminarModel

class WilcoxKOm08Model(LaminarModel):
    
    nStates = 3

    def __init__(self, vars, constants):
        local_constants = {
            'TurbModel__sigma_kine'  : 0.6,
            'TurbModel__sigma_omega' : 0.5,
            'TurbModel__beta_star'   : 0.09,
            'TurbModel__beta'        : 0.0708,
            'TurbModel__gamma'       : 13.0/25.0,
            'TurbModel__C_lim'       : 7.0/8.0,
            'TurbModel__sigma_d'     : 1.0/8.0,
        }
        local_constants.update(constants)
        super().__init__(vars, local_constants)
    
    @property
    def  sigma_kine(self): return self._constants['TurbModel__sigma_kine']
    @property
    def sigma_omega(self): return self._constants['TurbModel__sigma_omega']
    @property
    def   beta_star(self): return self._constants['TurbModel__beta_star']
    @property
    def        beta(self): return self._constants['TurbModel__beta']
    @property
    def       alpha(self): return self._constants['TurbModel__gamma']
    @property
    def       C_lim(self): return self._constants['TurbModel__C_lim']
    @property
    def     sigma_d(self): return self._constants['TurbModel__sigma_d']

    @property
    def       kine(self): return self._vars[     'phi'][1]
    @property
    def  grad_kine(self): return self._vars['grad_phi'][1]
    @property
    def  hess_kine(self): return self._vars['hess_phi'][1]
    
    @property
    def      omega(self): return self._vars[     'phi'][2]
    @property
    def grad_omega(self): return self._vars['grad_phi'][2]
    @property
    def hess_omega(self): return self._vars['hess_phi'][2]

    @property
    def omega_hat(self): return self.C_lim*self.grad_u/sqrt(self.beta_star)
    @property
    def grad_omega_hat(self): return self.C_lim*self.hess_u/sqrt(self.beta_star)

    @property
    def nuT(self): return self.kine / fmax(self.omega, self.omega_hat)
    @property
    def grad_nuT(self):
        if self.omega > self.omega_hat:
            return (self.grad_kine - self.grad_omega*self.nuT)/self.omega
        else:
            return (self.grad_kine - self.grad_omega_hat*self.nuT)/self.omega_hat

    @property
    def  kine_prod(self): return self.nuT * self.grad_u * self.grad_u
    @property
    def omega_prod(self): return self.alpha * self.omega / self.kine * self.kine_prod
    
    @property
    def  kine_dest(self): return self.beta_star * self.omega * self.kine
    @property
    def omega_dest(self): return self.beta * self.omega * self.omega
    
    @property
    def  kine_diff1(self): return (self.nu +  self.sigma_kine*self.nuT) * self.hess_kine
    @property
    def omega_diff1(self): return (self.nu + self.sigma_omega*self.nuT) * self.hess_omega
    
    @property
    def  kine_diff2(self): return self.sigma_kine  * self.grad_nuT * self.grad_kine
    @property
    def omega_diff2(self): return self.sigma_omega * self.grad_nuT * self.grad_omega
    
    @property
    def  kine_diff(self): return self.kine_diff1 + self.kine_diff2
    @property
    def omega_diff(self): return self.omega_diff1 + self.omega_diff2 + self.sigma_d * fmax(0.0, self.grad_kine*self.grad_omega) / self.omega
    
    @property
    def  kine_source(self): return self.kine_prod - self.kine_dest + self.kine_diff
    @property
    def omega_source(self): return self.omega_prod - self.omega_dest + self.omega_diff
    
    @property
    def scalarResiduals(self): return [self.kine_source, self.omega_source]