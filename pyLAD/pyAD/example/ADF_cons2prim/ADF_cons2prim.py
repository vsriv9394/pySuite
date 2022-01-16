import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/ArrayAD")
from ArrayAD import ArrayAD
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/JacobianAD")
from JacobianAD import JacobianAD
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/pyAD/example/ADF_cons2prim/libADF_cons2prim.so")

class ADF_cons2prim(C.Structure):

	_pack_ = 1
	_fields_ = [
		("___phi", C.c_double*25),
		("___psi", C.c_double*25),
		("Uc", C.POINTER(C.c_double)),
		("R", C.POINTER(C.c_double)),
		("gamma", C.POINTER(C.c_double)),
		("Up", C.POINTER(C.c_double)),
		("d_Up__d_Uc", C.POINTER(C.c_double)),
	]

	C_init = lib.init__ADF_cons2prim
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_calculate = lib.calculate__ADF_cons2prim
	C_calculate.restype = None
	C_calculate.argtypes = [
		C.c_void_p,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def calculate(
		self,
	):
		self.C_calculate(
			C.addressof(self),
		)

