import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/VarAD")
from VarAD import VarAD
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/JacAD")
from JacAD import JacAD
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_neumannBC/libADF_neumannBC.so")

class ADF_neumannBC(C.Structure):

	_pack_ = 1
	_fields_ = [
		("___phi", C.c_double*26),
		("___psi", C.c_double*26),
		("phi_0", C.POINTER(VarAD)),
		("phi_1", C.POINTER(VarAD)),
		("phi_2", C.POINTER(VarAD)),
		("y_b", C.POINTER(C.c_double)),
		("y_1", C.POINTER(C.c_double)),
		("y_2", C.POINTER(C.c_double)),
		("value", C.POINTER(C.c_double)),
		("R_phi", C.POINTER(VarAD)),
	]

	C_init = lib.init__ADF_neumannBC
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_setVars = lib.setVars__ADF_neumannBC
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
		C.c_void_p,
	]

	C_calculate = lib.calculate__ADF_neumannBC
	C_calculate.restype = None
	C_calculate.argtypes = [
		C.c_void_p,
	]

	C_setup = lib.setup__ADF_neumannBC
	C_setup.restype = None
	C_setup.argtypes = [
		C.c_void_p,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def setVars(
		self,
		phi_0,
		phi_1,
		phi_2,
		y_b,
		y_1,
		y_2,
		value,
		R_phi,
	):
		self.C_setVars(
			C.addressof(self),
			C.addressof(phi_0),
			C.addressof(phi_1),
			C.addressof(phi_2),
			C.addressof(y_b),
			C.addressof(y_1),
			C.addressof(y_2),
			C.addressof(value),
			C.addressof(R_phi),
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

