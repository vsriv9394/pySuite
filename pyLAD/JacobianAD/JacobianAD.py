import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/ArrayAD")
from ArrayAD import ArrayAD
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/JacobianAD/libJacobianAD.so")

class JacobianAD(C.Structure):

	_pack_ = 1
	_fields_ = [
		("M", C.c_int),
		("N", C.c_int),
		("m", C.c_int),
		("n", C.c_int),
		("offsets", C.POINTER(C.c_int)),
		("iBlocks", C.POINTER(C.c_int)),
		("entries", C.POINTER(C.c_double)),
		("inputs", C.POINTER(ArrayAD)),
		("outputs", C.POINTER(ArrayAD)),
	]

	C_init = lib.init__JacobianAD
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_delete = lib.delete__JacobianAD
	C_delete.restype = None
	C_delete.argtypes = [
		C.c_void_p,
	]

	C_calculate = lib.calculate__JacobianAD
	C_calculate.restype = None
	C_calculate.argtypes = [
		C.c_void_p,
	]

	C_create = lib.create__JacobianAD
	C_create.restype = None
	C_create.argtypes = [
		C.c_void_p,
		C.POINTER(ArrayAD),
		C.POINTER(ArrayAD),
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
		outputs,
		inputs,
	):
		self.C_create(
			C.addressof(self),
			outputs,
			inputs,
		)

