import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/VarAD")
from VarAD import VarAD
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/JacAD")
from JacAD import JacAD
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_residuals/libADF_residuals.so")

class ADF_residuals(C.Structure):

	_pack_ = 1
	_fields_ = [
		("___phi", C.c_double*83),
		("___psi", C.c_double*83),
		("phi", C.POINTER(VarAD)),
		("grad_phi", C.POINTER(VarAD)),
		("hess_phi", C.POINTER(VarAD)),
		("cb1", C.POINTER(VarAD)),
		("nu", C.POINTER(C.c_double)),
		("dpdx", C.POINTER(C.c_double)),
		("wallDist", C.POINTER(C.c_double)),
		("R_phi", C.POINTER(VarAD)),
	]

	C_init = lib.init__ADF_residuals
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_setVars = lib.setVars__ADF_residuals
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

	C_calculate = lib.calculate__ADF_residuals
	C_calculate.restype = None
	C_calculate.argtypes = [
		C.c_void_p,
	]

	C_setup = lib.setup__ADF_residuals
	C_setup.restype = None
	C_setup.argtypes = [
		C.c_void_p,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def setVars(
		self,
		phi,
		grad_phi,
		hess_phi,
		cb1,
		nu,
		dpdx,
		wallDist,
		R_phi,
	):
		self.C_setVars(
			C.addressof(self),
			C.addressof(phi),
			C.addressof(grad_phi),
			C.addressof(hess_phi),
			C.addressof(cb1),
			C.addressof(nu),
			C.addressof(dpdx),
			C.addressof(wallDist),
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

