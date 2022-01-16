import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/VarAD")
from VarAD import VarAD
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/JacAD")
from JacAD import JacAD
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_dirichiletBC/libADF_dirichiletBC.so")

class ADF_dirichiletBC(C.Structure):

	_pack_ = 1
	_fields_ = [
		("___phi", C.c_double*4),
		("___psi", C.c_double*4),
		("phi", C.POINTER(VarAD)),
		("value", C.POINTER(C.c_double)),
		("R_phi", C.POINTER(VarAD)),
	]

	C_init = lib.init__ADF_dirichiletBC
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_setVars = lib.setVars__ADF_dirichiletBC
	C_setVars.restype = None
	C_setVars.argtypes = [
		C.c_void_p,
		C.c_void_p,
		C.c_void_p,
		C.c_void_p,
	]

	C_calculate = lib.calculate__ADF_dirichiletBC
	C_calculate.restype = None
	C_calculate.argtypes = [
		C.c_void_p,
	]

	C_setup = lib.setup__ADF_dirichiletBC
	C_setup.restype = None
	C_setup.argtypes = [
		C.c_void_p,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def setVars(
		self,
		phi,
		value,
		R_phi,
	):
		self.C_setVars(
			C.addressof(self),
			C.addressof(phi),
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

