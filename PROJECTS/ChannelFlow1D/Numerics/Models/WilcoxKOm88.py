from .Laminar import LaminarModel

class WilcoxKOm88Model(LaminarModel):
    
    nStates = 3

    def __init__(self, vars, constants):
        local_constants = {
            'TurbModel__sigma_kine'  : 0.5,
            'TurbModel__sigma_omega' : 0.5,
            'TurbModel__beta_star'   : 0.09,
            'TurbModel__beta'        : 3.0/40.0,
            'TurbModel__gamma'       : 5.0/9.0,
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
    def      nuT(self): return self.kine / self.omega
    @property
    def grad_nuT(self): return (self.grad_kine-self.grad_omega*self.nuT)/self.omega

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
    def omega_diff(self): return self.omega_diff1 + self.omega_diff2
    
    @property
    def  kine_source(self): return self.kine_prod - self.kine_dest + self.kine_diff
    @property
    def omega_source(self): return self.omega_prod - self.omega_dest + self.omega_diff
    
    @property
    def scalarResiduals(self): return [self.kine_source, self.omega_source]