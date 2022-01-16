import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/VarAD")
from VarAD import VarAD
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/JacAD")
from JacAD import JacAD
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_deriv2/libADF_deriv2.so")

class ADF_deriv2(C.Structure):

	_pack_ = 1
	_fields_ = [
		("___phi", C.c_double*18),
		("___psi", C.c_double*18),
		("uL", C.POINTER(VarAD)),
		("uC", C.POINTER(VarAD)),
		("uR", C.POINTER(VarAD)),
		("yL", C.POINTER(C.c_double)),
		("yC", C.POINTER(C.c_double)),
		("yR", C.POINTER(C.c_double)),
		("d2udy2", C.POINTER(VarAD)),
	]

	C_init = lib.init__ADF_deriv2
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_setVars = lib.setVars__ADF_deriv2
	C_setVars.restype = None
	C_setVars.argtypes = [
		C.c_void_p,
		C.c_void_p,
		C.c_void_p,
		C.c_void_p,
		C.c_void_p,
		C.c_void_p,
		C.c_void_p,
		C.c_void_p,
	]

	C_calculate = lib.calculate__ADF_deriv2
	C_calculate.restype = None
	C_calculate.argtypes = [
		C.c_void_p,
	]

	C_setup = lib.setup__ADF_deriv2
	C_setup.restype = None
	C_setup.argtypes = [
		C.c_void_p,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def setVars(
		self,
		uL,
		uC,
		uR,
		yL,
		yC,
		yR,
		d2udy2,
	):
		self.C_setVars(
			C.addressof(self),
			C.addressof(uL),
			C.addressof(uC),
			C.addressof(uR),
			C.addressof(yL),
			C.addressof(yC),
			C.addressof(yR),
			C.addressof(d2udy2),
		)

	def calculate(
		self,
	):
		self.C_calculate(
			C.addressof(self),
		)

	def setup(
		self,
	):
		self.C_setup(
			C.addressof(self),
		)

