import numpy as np
import ctypes as C
from scipy.sparse import csr_matrix, diags
from scipy.sparse.linalg.isolve import lgmres

def getDataFrom(Cdata):
    
    y = np.ctypeslib.as_array(Cdata.y, shape=[Cdata.nPoints])
    U = np.ctypeslib.as_array(Cdata.U_values, shape=[Cdata.nPoints, Cdata.nStates])
    R = np.ctypeslib.as_array(Cdata.R_values, shape=[Cdata.nPoints-2, Cdata.nStates])
    
    J_offsets = np.ctypeslib.as_array(Cdata.J.offsets, shape=[Cdata.J.nRows+1])
    J_colIds  = np.ctypeslib.as_array(Cdata.J.colIds,  shape=[J_offsets[-1]])
    J_elems   = np.ctypeslib.as_array(Cdata.J.elems,   shape=[J_offsets[-1]])
    
    J = csr_matrix((J_elems, J_colIds, J_offsets), shape=[Cdata.J.nRows, Cdata.J.nCols])
    
    return y, U, R, J

def getBackwardEulerUpdate(invDt, J, R, dU=None, **options):
    return lgmres(diags(invDt.ravel())-J, R.ravel(), x0=dU, **options)[0]

def calculateDpdx(ReTau, nu):
    uTau = ReTau * nu
    return -uTau**2

def calcCfl(cfl, maxCfl=1e3, rampFactor=1.03, rampFlag=True):
    if rampFlag: cfl *= rampFactor
    return cfl if cfl < maxCfl else maxCfl

def printResidualNorms(iSolverIter, R):
    line = '%9d' % (iSolverIter)
    for i in range(R.shape[1]):
        line += ' %.6le' % (np.linalg.norm(R[:,i]))
    print(line)