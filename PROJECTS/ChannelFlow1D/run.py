import sys, os
from subprocess import call
from config import *

print('Compiling ADFs...')
compileADFs(config['TurbModel'], adfList=[dirichiletBC, neumannBC, deriv1, deriv2])
os.chdir('Channel')
call('pymake > log', shell=True)
os.chdir('..')

print('Setting up data structures...')
from Channel.Channel import Channel

channel = Channel()

channel.nu = config['nu']
channel.dpdx = config['dpdx']
channel.nPoints = config['nPoints']
channel.nStates = config['TurbModel'].nStates

channel.setup(0.1/config['ReTau'])

y, U, R, J = getDataFrom(channel)

## Wall BC ##############################################################################

channel.wallBC[0] = 0.0
channel.wallBC[1] = 0.0
#channel.wallBC[2] = 6.0 * config['nu'] / 0.075 / (0.1/config['ReTau'])**2

## Initial Conditions ###################################################################
if os.path.exists("solution.npy"):
    
    U *= 0.0
    U += np.load("solution.npy")
    #print(U)

else:
    
    U *= 0.0
    U[:,0] += 0.0
    U[:,1] += 1e-8
    #U[:,2] += 1e-5

## Solve ################################################################################
#'''
#dU = None
#nStates = config['TurbModel'].nStates
#invDt = np.zeros((y.size-2,nStates))
#for i in range(nStates): invDt[:,i] = 1.0/config['cfl']/(y[2:]-y[:-2])
#
#for iSolverIter in range(config['nSolverIters']):
#    
#    channel.calculate()
#    printResidualNorms(iSolverIter, R)
#    config['cfl'] = calcCfl(config['cfl'], maxCfl=1e3, rampFlag=iSolverIter>1000)
#    dU = getBackwardEulerUpdate(invDt, J, R, dU=dU, tol=1e-12, maxiter=5)
#    U[1:-1,:] += np.reshape(dU, R.shape)
#
#np.save('mesh.npy', y)
#np.save('solution.npy', U)
#np.save('residual.npy', R)
#'''

## Velocity plots #######################################################################
'''
dpdx = config['dpdx']
nu = config['nu']

inlinePlot('velProf', y, -0.5*(dpdx/nu)*y*(2-y), lw=2, c='r', show=False)

inlinePlot('velProf', y, U[:,0], lw=2, c='b', marker='o', xlabel='y', ylabel='U',
           xlim={'left':0,'right':1}, ylim={'top':1,'bottom':0})
#'''

## Log law plots ########################################################################
#'''
uTau = config['ReTau'] * config['nu']

inlinePlot('y_vs_U', y[1:]*config['ReTau'], 5+np.log(y[1:]*config['ReTau'])/0.41,
           kind='semilogx', ls='-', lw=2, c='r', show=False)

inlinePlot('y_vs_U', y*config['ReTau'], y*config['ReTau'], show=False,
           kind='semilogx', ls='-', lw=2, c='g')

inlinePlot('y_vs_U', y*config['ReTau'], U[:,0]/uTau, xlabel='y', ylabel='U',
           kind='semilogx', ls='-', lw=2, c='b', marker='o', show=True,
           xlim={'left':0.1, 'right':config['ReTau']}, ylim={'top':32, 'bottom':0})
#'''

## Don't forget to delete! ##############################################################

channel.delete()
