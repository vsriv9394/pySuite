import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/pyad/VarAD")
from VarAD import VarAD
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/pyad/JacAD/libJacAD.so")

class JacAD(C.Structure):

	_pack_ = 1
	_fields_ = [
		("nRows", C.c_int),
		("nCols", C.c_int),
		("offsets", C.POINTER(C.c_int)),
		("colIds", C.POINTER(C.c_int)),
		("elems", C.POINTER(C.c_double)),
		("inputs", C.POINTER(VarAD)),
		("outputs", C.POINTER(VarAD)),
	]

	C_init = lib.init__JacAD
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_delete = lib.delete__JacAD
	C_delete.restype = None
	C_delete.argtypes = [
		C.c_void_p,
	]

	C_calculate = lib.calculate__JacAD
	C_calculate.restype = None
	C_calculate.argtypes = [
		C.c_void_p,
	]

	C_create = lib.create__JacAD
	C_create.restype = None
	C_create.argtypes = [
		C.c_void_p,
		C.c_int,
		C.c_int,
		C.POINTER(VarAD),
		C.POINTER(VarAD),
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

	def create(
		self,
		nInputs,
		nOutputs,
		inputs,
		outputs,
	):
		self.C_create(
			C.addressof(self),
			nInputs,
			nOutputs,
			inputs,
			outputs,
		)

