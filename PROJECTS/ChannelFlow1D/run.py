import sys, os
from subprocess import call
from config import *

#'''###########################################################################
# Compilation Section
#---------------------
adfList = [dirichiletBC, neumannBC, deriv1, deriv2]
compileADFs(config['TurbModel'], adfList=adfList)
os.chdir('Channel'); call('pymake > log', shell=True); os.chdir('..')
#'''###########################################################################

#'''###########################################################################
# Setup channel
#---------------
from Channel.Channel import Channel
channel = Channel()
channel.cb1.data = 0.1355
channel.nu = config['nu']
channel.dpdx = config['dpdx']
channel.nPoints = config['nPoints']
channel.nStates = config['TurbModel'].nStates
channel.setup(0.1/config['ReTau'])
y, U, R, J = getDataFrom(channel)
#'''###########################################################################

#'''###########################################################################
# Initial Conditions
#--------------------
U *= 0.0
if os.path.exists("solution.npy"):
    U += np.load("solution.npy")
else:
    for iState in range(channel.nStates):
        U[:,iState] += config['InitialConditions'][iState]
#'''###########################################################################

#'''###########################################################################
# Boundary Conditions
#---------------------
for iState in range(channel.nStates):
    channel.wallBC[iState] = config['WallBoundaryConditions'][iState]
#'''###########################################################################

'''###########################################################################
# Solver
#--------
dU = None
nStates = config['TurbModel'].nStates
invDt = np.zeros((y.size,nStates))
for j in range(nStates):
    invDt[0,j] = 1.0/(y[1]-y[0])
    invDt[-1,j] = 1.0/(y[-1]-y[-2])
    invDt[1:-1,j] = 1.0/(y[2:]-y[:-2])
for iSolverIter in range(config['nSolverIters']):
    channel.calculate()
    print(config['cfl'])
    printResidualNorms(iSolverIter, R)
    config['cfl'] = calcCfl(config['cfl'], maxCfl=2000,
                            rampFactor=1.001, rampFlag=iSolverIter>1000)
    dU = getBackwardEulerUpdate(invDt/config['cfl'], J, R, dU=dU, tol=1e-12, maxiter=5)
    U[:,:] += 0.05 * np.reshape(dU, U.shape)
    U[U<0.0] = 1e-9
np.save('mesh.npy', y)
np.save('solution.npy', U)
#'''###########################################################################

#'''###########################################################################
# Check Jacobians
#-----------------
fd_step = 1e-6
channel.calculate()
R_baseline = R.copy()
J_ad = J.todense().copy()

errorList = []
R_index = 0
for iR in range(R.shape[0]):
    for jR in range(R.shape[1]):
        U_index = 0
        for iU in range(U.shape[0]):
            for jU in range(U.shape[1]):
                step = np.maximum(fd_step * np.abs(U[iU,jU]), 1e-15)
                U[iU,jU] += step
                channel.calculate();
                U[iU,jU] -= step
                J_fd_elem = (R[iR,jR] - R_baseline[iR,jR]) / step
                if J_fd_elem!=0 or J_ad[R_index,U_index]!=0:
                    print('(%2d,%2d) (%2d,%2d) %+le %+le' % (\
                        iR, jR, iU, jU, J_ad[R_index, U_index], J_fd_elem))
                    if abs(J_fd_elem)>1e-12:
                        errorList.append(abs((J_ad[R_index, U_index]-J_fd_elem)/J_fd_elem))
                U_index += 1
        R_index += 1

plt.semilogy(errorList)
plt.xlabel("Jacobian entry id")
plt.ylabel("Relative error")
plt.show()
#'''###########################################################################

'''###########################################################################
# Print cb1 jacobians
#---------------------
print(channel.J_cb1.nRows)
print(channel.J_cb1.nCols)
for i in range(channel.J_cb1.nRows):
    for j in range(channel.J_cb1.offsets[i], channel.J_cb1.offsets[i+1]):
        print(i, channel.J_cb1.colIds[j], channel.J_cb1.elems[j])
#'''###########################################################################

'''###########################################################################
# Velocity plots
#----------------
dpdx = config['dpdx']
nu = config['nu']

inlinePlot('velProf', y, -0.5*(dpdx/nu)*y*(2-y),
           lw=2, c='r', show=False)

inlinePlot('velProf', y, U[:,0],
           lw=2, c='b', marker='o',
           xlabel='y', ylabel='U',
           xlim={'left':0,'right':1},
           ylim={'top':1,'bottom':0})
#'''###########################################################################

'''###########################################################################
# Log law plots
#---------------
yPlus = y*config['ReTau']
uPlus = U[:,0]/config['ReTau']/config['nu']
idealViscousSubLayer = y*config['ReTau']
idealLogLayer = (1/0.41) * np.log(y[1:]*config['ReTau']) + 5.0

inlinePlot('y_vs_U', yPlus, idealViscousSubLayer, kind='semilogx',
           ls='-', lw=2, c='r', show=False)

inlinePlot('y_vs_U', yPlus[1:], idealLogLayer, kind='semilogx',
           ls='-', lw=2, c='g', show=False)

inlinePlot('y_vs_U', yPlus, uPlus, kind='semilogx',
           ls='-', lw=2, c='b', marker='o',
           xlabel='y', ylabel='U',
           xlim={'left':yPlus[1], 'right':yPlus[-1]},
           ylim={'top':25, 'bottom':0})
#'''###########################################################################

#'''###########################################################################
# Don't forget to delete!
#-------------------------
channel.delete()
#'''###########################################################################
