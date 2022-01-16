import sys, os
import ctypes as C

lib = C.CDLL("/home/vsriv/codes/pySuite/pyad/VarAD/libVarAD.so")

class VarAD(C.Structure):

	_pack_ = 1
	_fields_ = [
		("data", C.c_double),
		("nDeps", C.c_int),
		("depPtrs", C.POINTER(C.c_void_p)),
		("depSens", C.POINTER(C.c_double)),
	]

	C_setupDeps = lib.setupDeps__VarAD
	C_setupDeps.restype = None
	C_setupDeps.argtypes = [
		C.c_void_p,
		C.c_int,
		C.POINTER(C.c_void_p),
	]

	C_init = lib.init__VarAD
	C_init.restype = None
	C_init.argtypes = [
		C.c_void_p,
	]

	C_delete = lib.delete__VarAD
	C_delete.restype = None
	C_delete.argtypes = [
		C.c_void_p,
	]

	C_calculateLinear = lib.calculateLinear__VarAD
	C_calculateLinear.restype = None
	C_calculateLinear.argtypes = [
		C.c_void_p,
	]

	def __init__(self):
		self.C_init(C.addressof(self))

	def setupDeps(
		self,
		nDeps,
		depPtrs,
	):
		self.C_setupDeps(
			C.addressof(self),
			nDeps,
			depPtrs,
		)

	def delete(
		self,
	):
		self.C_delete(
			C.addressof(self),
		)

	def calculateLinear(
		self,
	):
		self.C_calculateLinear(
			C.addressof(self),
		)

