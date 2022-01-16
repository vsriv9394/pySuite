#include "../ADF_deriv2.h"
#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/defineOps.h"

static void calculateDerivatives(ADF_deriv2 *self);
static void updateDerivs(ADF_deriv2 *self, VarAD *output);
static void updateAllDerivs(ADF_deriv2 *self, int size);
static void setInputs(ADF_deriv2 *self);
static void getOutputs(ADF_deriv2 *self, int size);

void calculate__ADF_deriv2
(
	void *_self
)
{
	ADF_deriv2 *self = _self;
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	setInputs(self);
	SUB(6, 1, 0)
	SUB(7, 4, 3)
	DIV(8, 6, 7)
	SUB(9, 2, 1)
	SUB(10, 5, 4)
	DIV(11, 9, 10)
	SUB(12, 11, 8)
	CONST(13, 2.0000000000e+00)
	MUL(14, 13, 12)
	SUB(15, 5, 3)
	DIV(16, 14, 15)
	EQUAL(17, 16)
	getOutputs(self, 18);
	#ifndef DISABLE_DERIVS
	updateAllDerivs(self, 18);
	#endif
}

static void calculateDerivatives(ADF_deriv2 *self)
{
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	D_EQUAL(17, 16)
	D_DIV(16, 14, 15)
	D_SUB(15, 5, 3)
	D_MUL(14, 13, 12)
	D_SUB(12, 11, 8)
	D_DIV(11, 9, 10)
	D_SUB(10, 5, 4)
	D_SUB(9, 2, 1)
	D_DIV(8, 6, 7)
	D_SUB(7, 4, 3)
	D_SUB(6, 1, 0)
}

#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/undefOps.h"

static void updateDerivs(ADF_deriv2 *self, VarAD *output)
{
	int iInput = 0;
	for(int i=0; i<1; i++)
	{
		output->depSens[iInput] = self->___psi[iInput]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		output->depSens[iInput] = self->___psi[iInput]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		output->depSens[iInput] = self->___psi[iInput]; iInput++;
	}
}

static void updateAllDerivs(ADF_deriv2 *self, int size)
{
	int iOutput = size-1;
	for(int j=0; j>=0; j--)
	{
		for(int iVar=0; iVar<size; iVar++) self->___psi[iVar] = 0.0;
		VarAD *output = self->d2udy2+j;
		self->___psi[iOutput] = 1.0; iOutput--;
		calculateDerivatives(self);
		updateDerivs(self, output);
	}
}

static void setInputs(ADF_deriv2 *self)
{
	int iInput = 0;
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->uL[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->uC[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->uR[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->yL[i]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->yC[i]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->yR[i]; iInput++;
	}
}

static void getOutputs(ADF_deriv2 *self, int size)
{
	int iOutput = size-1;
	for(int i=0; i>=0; i--)
	{
		self->d2udy2[i].data = self->___phi[iOutput]; iOutput--;
	}
}

