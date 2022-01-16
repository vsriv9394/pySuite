import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/VarAD")
from VarAD import VarAD
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/JacAD")
from JacAD import JacAD
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_deriv1")
from ADF_deriv1 import ADF_deriv1
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_deriv2")
from ADF_deriv2 import ADF_deriv2
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_dirichiletBC")
from ADF_dirichiletBC import ADF_dirichiletBC
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_neumannBC")
from ADF_neumannBC import ADF_neumannBC
sys.path.pop(0)

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/ADF/ADF_residuals")
from ADF_residuals import ADF_residuals
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/ChannelFlow1D/Channel/libChannel.so")

class Channel(C.Structure):

	_pack_ = 1
	_fields_ = [
		("nPoints", C.c_int),
		("nStates", C.c_int),
		("nu", C.c_double),
		("dpdx", C.c_double),
		("wallBC", C.POINTER(C.c_double)),
		("y", C.POINTER(C.c_double)),
		("U_values", C.POINTER(C.c_double)),
		("R_values", C.POINTER(C.c_double)),
		("U", C.POINTER(VarAD)),
		("U_y", C.POINTER(VarAD)),
		("U_yy", C.POINTER(VarAD)),
		("R", C.POINTER(VarAD)),
		("cb1", VarAD),
		("J", JacAD),
		("J_cb1", JacAD),
	]

	C_init = lib.init__Channel
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_delete = lib.delete__Channel
	C_delete.restype = None
	C_delete.argtypes = [
		C.c_void_p,
	]

	C_calculate = lib.calculate__Channel
	C_calculate.restype = None
	C_calculate.argtypes = [
		C.c_void_p,
	]

	C_setup = lib.setup__Channel
	C_setup.restype = None
	C_setup.argtypes = [
		C.c_void_p,
		C.c_double,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def delete(
		self,
	):
		self.C_delete(
			C.addressof(self),
		)

	def calculate(
		self,
	):
		self.C_calculate(
			C.addressof(self),
		)

	def setup(
		self,
		dy_0,
	):
		self.C_setup(
			C.addressof(self),
			dy_0,
		)

