import sys, os
import ctypes as C

lib = C.CDLL("/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/SensAD/libSensAD.so")

class SensAD(C.Structure):

	_pack_ = 1
	_fields_ = [
		("arrayAD", C.c_void_p),
		("indices", C.POINTER(C.c_int)),
		("entries", C.POINTER(C.c_double)),
		("indicesIsACopy", C.c_int),
		("entriesIsACopy", C.c_int),
	]

	C_init = lib.init__SensAD
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_delete = lib.delete__SensAD
	C_delete.restype = None
	C_delete.argtypes = [
		C.c_void_p,
	]

	C_create = lib.create__SensAD
	C_create.restype = None
	C_create.argtypes = [
		C.c_void_p,
		C.c_void_p,
		C.POINTER(C.c_int),
		C.POINTER(C.c_double),
		C.c_int,
		C.c_int,
		C.c_int,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def delete(
		self,
	):
		self.C_delete(
			C.addressof(self),
		)

	def create(
		self,
		arrayAD,
		indices,
		entries,
		naturalIndexing,
		nElems,
		elemSize,
	):
		self.C_create(
			C.addressof(self),
			C.addressof(arrayAD),
			indices,
			entries,
			naturalIndexing,
			nElems,
			elemSize,
		)

