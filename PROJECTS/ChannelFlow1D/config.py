from Numerics import *
from Utils import *

config = { }

config['nPoints'] = 200
config['nu'] = 1e-6
config['ReTau'] = 5200
config['dpdx'] = \
    calculateDpdx(config['ReTau'], config['nu'])

config['TurbModel'] = SpalartAllmaras92Model
config['InitialConditions'] = [
    1e-1,
    1e-8,
    1e-2
]
config['WallBoundaryConditions'] = [
    0.0,
    0.0,
    6.0*config['nu'] / 0.075 / (0.1/config['ReTau'])**2
]

config['cfl'] = 2000
config['nSolverIters'] = 5000
