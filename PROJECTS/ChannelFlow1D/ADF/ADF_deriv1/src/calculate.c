#include "../ADF_deriv1.h"
#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/defineOps.h"

static void calculateDerivatives(ADF_deriv1 *self);
static void updateDerivs(ADF_deriv1 *self, VarAD *output);
static void updateAllDerivs(ADF_deriv1 *self, int size);
static void setInputs(ADF_deriv1 *self);
static void getOutputs(ADF_deriv1 *self, int size);

void calculate__ADF_deriv1
(
	void *_self
)
{
	ADF_deriv1 *self = _self;
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	setInputs(self);
	SUB(6, 1, 0)
	SUB(7, 4, 3)
	DIV(8, 6, 7)
	SUB(9, 2, 1)
	SUB(10, 5, 4)
	DIV(11, 9, 10)
	ADD(12, 8, 11)
	CONST(13, 5.0000000000e-01)
	MUL(14, 13, 12)
	EQUAL(15, 14)
	getOutputs(self, 16);
	#ifndef DISABLE_DERIVS
	updateAllDerivs(self, 16);
	#endif
}

static void calculateDerivatives(ADF_deriv1 *self)
{
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	D_EQUAL(15, 14)
	D_MUL(14, 13, 12)
	D_ADD(12, 8, 11)
	D_DIV(11, 9, 10)
	D_SUB(10, 5, 4)
	D_SUB(9, 2, 1)
	D_DIV(8, 6, 7)
	D_SUB(7, 4, 3)
	D_SUB(6, 1, 0)
}

#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/undefOps.h"

static void updateDerivs(ADF_deriv1 *self, VarAD *output)
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

static void updateAllDerivs(ADF_deriv1 *self, int size)
{
	int iOutput = size-1;
	for(int j=0; j>=0; j--)
	{
		for(int iVar=0; iVar<size; iVar++) self->___psi[iVar] = 0.0;
		VarAD *output = self->dudy+j;
		self->___psi[iOutput] = 1.0; iOutput--;
		calculateDerivatives(self);
		updateDerivs(self, output);
	}
}

static void setInputs(ADF_deriv1 *self)
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

static void getOutputs(ADF_deriv1 *self, int size)
{
	int iOutput = size-1;
	for(int i=0; i>=0; i--)
	{
		self->dudy[i].data = self->___phi[iOutput]; iOutput--;
	}
}

