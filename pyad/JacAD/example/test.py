import ctypes as C
import numpy as np
from pyad.JacAD.JacAD import JacAD, VarAD

def ptrTo(var, dtype=None):
    if dtype==None: return C.cast(C.addressof(var), C.c_void_p)
    else: return C.cast(C.addressof(var), C.POINTER(dtype))

x = VarAD()
y = VarAD()
z = VarAD()
J = JacAD()

x.create(2)
y.create(2)
z.create(2)

y.initDeps(2, None, None)
z.initDeps(2, None, None)

y.depVars[0] = C.addressof(x)
y.depVars[1] = C.addressof(x)
z.depVars[0] = C.addressof(y)
z.depVars[1] = C.addressof(y)
for i in range(2):
    for j in range(2):
        y.depIds[i*2+j] = j
        z.depIds[i*2+j] = j

J.create(x, z)

z.depSens[0] = 1
z.depSens[1] = 2
z.depSens[2] = 3
z.depSens[3] = 4

y.depSens[0] = 5
y.depSens[1] = 6
y.depSens[2] = 7
y.depSens[3] = 8

J.calculate()

for i in range(z.size):
    for j in range(J.offsets[i],J.offsets[i+1]):
        print('%d %d %le' % (i, J.colIds[j], J.elems[j]))

x.delete()
y.delete()
z.delete()
J.delete()