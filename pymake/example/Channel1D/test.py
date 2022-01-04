from Channel1D import Channel1D
import ctypes as C
import numpy as np
import matplotlib.pyplot as plt

channel = Channel1D()
channel.create(21, 0.01, 0, 1)
print("Third element = %le" % channel.mesh.x[2])
y = np.ctypeslib.as_array(channel.mesh.x, shape=[channel.mesh.nNodes])
U = np.ctypeslib.as_array(
    C.cast(channel.U, C.POINTER(C.c_double)),
    shape=[channel.mesh.nNodes,2]
)
U *= 0.0
U[:,0] += 2.0
U[:,1] += 3.0
plt.plot(np.linspace(0, 1, 21), y, '-o')
plt.show()
plt.plot(np.linspace(0, 1, 21), U[:,0], '-o')
plt.show()
channel.delete()
