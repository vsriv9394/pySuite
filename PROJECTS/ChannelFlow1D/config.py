from Numerics import *
from Utils import *

config = { }

config['TurbModel'] = SpalartAllmaras92Model

config['nPoints'] = 80

config['nu'] = 1e-6
config['ReTau'] = 950
config['dpdx'] = calculateDpdx(config['ReTau'], config['nu'])

config['cfl'] = 100
config['nSolverIters'] = 40000