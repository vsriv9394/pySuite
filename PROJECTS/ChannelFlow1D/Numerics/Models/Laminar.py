from pyad.pyAD import *

class LaminarModel:

    nStates = 1

    def __init__(self, vars, constants):
        self._vars      = vars
        self._constants = { 'nu': 1e-6, 'dpdx':2e-6, 'wallDist':0.0 }
        self._constants.update(constants)

    @property
    def     nu(self): return self._constants['nu']
    @property
    def   dpdx(self): return self._constants['dpdx']
    @property
    def      d(self): return self._constants['wallDist']
    
    @property
    def      u(self): return self._vars['phi'][0]
    @property
    def grad_u(self): return self._vars['grad_phi'][0]
    @property
    def hess_u(self): return self._vars['hess_phi'][0]

    @property
    def scalarResiduals(self): return []
    @property
    def nuT(self): 0 #return 10 * self.nu * self.d
    @property
    def grad_nuT(self): 0 #return 10 * self.nu
    
    @property
    def residuals(self):
        
        res_u = -self.dpdx + self.nu * self.hess_u + \
                 self.nuT * self.hess_u + self.grad_nuT * self.grad_u
        
        return { 'R_phi': [res_u] + self.scalarResiduals }