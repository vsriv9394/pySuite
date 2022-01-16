#include "../ADF_cons2prim.h"
#include "/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/pyAD/headers/defineOps.h"

static void calculateDerivatives(ADF_cons2prim *self);
static void updateDerivs(ADF_cons2prim *self, int size);
static void setInputs(ADF_cons2prim *self);
static void getOutputs(ADF_cons2prim *self, int size);

void calculate__ADF_cons2prim
(
	void *_self
)
{
	ADF_cons2prim *self = _self;
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	setInputs(self);
	DIV(6, 1, 0)
	DIV(7, 2, 0)
	CONST(8, 1.0000000000e+00)
	SUB(9, 5, 8)
	CONST(10, 5.0000000000e-01)
	MUL(11, 10, 0)
	CONST(12, 2.0000000000e+00)
	POW(13, 6, 12)
	POW(14, 7, 12)
	ADD(15, 13, 14)
	MUL(16, 11, 15)
	SUB(17, 3, 16)
	MUL(18, 9, 17)
	ADD(19, 3, 18)
	DIV(20, 19, 0)
	if(___phi[0]>___phi[8])
	{
		EQUAL(21, 18)
		EQUAL(22, 6)
		EQUAL(23, 7)
		EQUAL(24, 20)
		getOutputs(self, 25);
		#ifndef DISABLE_DERIVS
		updateDerivs(self, 25);
		#endif
	}
	else
	{
		EQUAL(21, 0)
		EQUAL(22, 6)
		EQUAL(23, 7)
		EQUAL(24, 18)
		getOutputs(self, 25);
		#ifndef DISABLE_DERIVS
		updateDerivs(self, 25);
		#endif
	}
}

static void calculateDerivatives(ADF_cons2prim *self)
{
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	if(___phi[0]<=___phi[8])
	{
		D_EQUAL(24, 18)
		D_EQUAL(23, 7)
		D_EQUAL(22, 6)
		D_EQUAL(21, 0)
	}
	else
	{
		D_EQUAL(24, 20)
		D_EQUAL(23, 7)
		D_EQUAL(22, 6)
		D_EQUAL(21, 18)
	}
	D_DIV(20, 19, 0)
	D_ADD(19, 3, 18)
	D_MUL(18, 9, 17)
	D_SUB(17, 3, 16)
	D_MUL(16, 11, 15)
	D_ADD(15, 13, 14)
	D_POW(14, 7, 12)
	D_POW(13, 6, 12)
	D_MUL(11, 10, 0)
	D_SUB(9, 5, 8)
	D_DIV(7, 2, 0)
	D_DIV(6, 1, 0)
}

#include "/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/pyAD/headers/undefOps.h"

static void updateDerivs(ADF_cons2prim *self, int size)
{
	int iOutput, iSens, iInput;
	iOutput = size-1;
	for(int j=3; j>=0; j--)
	{
		for(int iVar=0; iVar<size; iVar++) self->___psi[iVar] = 0.0;
		self->___psi[iOutput--] = 1.0;
		calculateDerivatives(self);
		iInput = 0;
		for(int i=0; i<4; i++)
		{
			self->d_Up__d_Uc[j*4+i] = self->___psi[iInput++];
		}
	}
}

static void setInputs(ADF_cons2prim *self)
{
	int iInput = 0;
	for(int i=0; i<4; i++)
	{
		self->___phi[iInput++] = self->Uc[i];
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput++] = self->R[i];
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput++] = self->gamma[i];
	}
}

static void getOutputs(ADF_cons2prim *self, int size)
{
	int iOutput = size-1;
	for(int i=3; i>=0; i--)
	{
		self->Up[i] = self->___phi[iOutput--];
	}
}

