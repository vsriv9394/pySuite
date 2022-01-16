import sys, os
import ctypes as C

sys.path.insert(0, "/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/SensAD")
from SensAD import SensAD
sys.path.pop(0)

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/ArrayAD/libArrayAD.so")

class ArrayAD(C.Structure):

	_pack_ = 1
	_fields_ = [
		("shape", C.c_int*4),
		("eSize", C.c_int),
		("nDeps", C.c_int),
		("data", C.POINTER(C.c_double)),
		("deps", C.POINTER(SensAD)),
	]

	C_setNumDeps = lib.setNumDeps__ArrayAD
	C_setNumDeps.restype = None
	C_setNumDeps.argtypes = [
		C.c_void_p,
		C.c_int,
	]

	C_init = lib.init__ArrayAD
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_delete = lib.delete__ArrayAD
	C_delete.restype = None
	C_delete.argtypes = [
		C.c_void_p,
	]

	C_create = lib.create__ArrayAD
	C_create.restype = None
	C_create.argtypes = [
		C.c_void_p,
	]

	C_calculateLinear = lib.calculateLinear__ArrayAD
	C_calculateLinear.restype = None
	C_calculateLinear.argtypes = [
		C.c_void_p,
	]

	C_setDep = lib.setDep__ArrayAD
	C_setDep.restype = None
	C_setDep.argtypes = [
		C.c_void_p,
		C.c_int,
		C.c_void_p,
		C.POINTER(C.c_int),
		C.POINTER(C.c_double),
		C.c_int,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def setNumDeps(
		self,
		nDeps,
	):
		self.C_setNumDeps(
			C.addressof(self),
			nDeps,
		)

	def delete(
		self,
	):
		self.C_delete(
			C.addressof(self),
		)

	def create(
		self,
	):
		self.C_create(
			C.addressof(self),
		)

	def calculateLinear(
		self,
	):
		self.C_calculateLinear(
			C.addressof(self),
		)

	def setDep(
		self,
		iDep,
		arrayAD,
		indices,
		entries,
		naturalIndexing,
	):
		self.C_setDep(
			C.addressof(self),
			iDep,
			C.addressof(arrayAD),
			indices,
			entries,
			naturalIndexing,
		)

