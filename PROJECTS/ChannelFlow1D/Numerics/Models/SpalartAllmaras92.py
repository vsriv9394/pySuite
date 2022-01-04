from pyad.pyAD import *
from .Laminar import LaminarModel

class SpalartAllmaras92Model(LaminarModel):
    
    nStates = 2

    def __init__(self, vars, constants):
        local_constants = {
            'TurbModel__cb1'       : 0.1355,
            'TurbModel__cb2'       : 0.622,
            'TurbModel__inv_sigma' : 1.5,
            'TurbModel__kappa'     : 0.41,
            'TurbModel__cw2'       : 0.3,
            'TurbModel__cw3'       : 2.0,
            'TurbModel__cv1'       : 7.1,
        }
        local_constants.update(constants)
        super().__init__(vars, local_constants)
    
    @property
    def       cb1(self): return self._constants['TurbModel__cb1']
    @property
    def       cb2(self): return self._constants['TurbModel__cb2']
    @property
    def inv_sigma(self): return self._constants['TurbModel__inv_sigma']
    @property
    def     kappa(self): return self._constants['TurbModel__kappa']
    @property
    def       cw2(self): return self._constants['TurbModel__cw2']
    @property
    def       cw3(self): return self._constants['TurbModel__cw3']
    @property
    def       cv1(self): return self._constants['TurbModel__cv1']
    @property
    def       cw1(self): return self.cb1/self.kappa**2 + (1+self.cb2)*self.inv_sigma

    @property
    def       nuSA(self): return self._vars[     'phi'][1]
    @property
    def  grad_nuSA(self): return self._vars['grad_phi'][1]
    @property
    def  hess_nuSA(self): return self._vars['hess_phi'][1]

    @property
    def nuT(self): return self.fv1 * self.nuSA
    @property
    def fv1(self): return self.chi**3 / (self.chi**3 + self.cv1**3)
    @property
    def chi(self): return self.nuSA / self.nu

    @property
    def grad_nuT(self): return self.grad_fv1 * self.nuSA + self.fv1 * self.grad_nuSA
    @property
    def grad_fv1(self): return (3 / self.chi) * self.fv1 * (1 - self.fv1) * self.grad_chi
    @property
    def grad_chi(self): return self.grad_nuSA / self.nu

    @property
    def S_hat(self): return self.grad_u + (self.nuSA / (self.kappa * self.d)**2) * self.fv2
    @property
    def   fv2(self): return 1 - self.chi / (1 + self.chi * self.fv1)
    
    @property
    def fw(self): return self.g * ( (1 + self.cw3**6) / (self.g**6 + self.cw3**6) ) ** (1.0 / 6.0)
    @property
    def  g(self): return self.r + self.cw2 * (self.r**6 - self.r)
    @property
    def  r(self): return fmin((self.nuSA / (self.kappa * self.d)**2) / self.S_hat, 10)
    
    @property
    def  prod(self): return self.cb1 * self.S_hat * self.nuSA
    @property
    def  dest(self): return self.cw1 * self.fw * (self.nuSA / self.d)**2
    @property
    def diff1(self): return self.inv_sigma * (self.nu + self.nuSA) * self.hess_nuSA
    @property
    def diff2(self): return self.inv_sigma * (1 + self.cb2) * self.grad_nuSA * self.grad_nuSA
    
    @property
    def scalarResiduals(self): return [self.prod - self.dest + self.diff1 + self.diff2]