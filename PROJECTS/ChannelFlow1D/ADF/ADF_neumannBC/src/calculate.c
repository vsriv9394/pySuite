#include "../ADF_neumannBC.h"
#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/defineOps.h"

static void calculateDerivatives(ADF_neumannBC *self);
static void updateDerivs(ADF_neumannBC *self, VarAD *output);
static void updateAllDerivs(ADF_neumannBC *self, int size);
static void setInputs(ADF_neumannBC *self);
static void getOutputs(ADF_neumannBC *self, int size);

void calculate__ADF_neumannBC
(
	void *_self
)
{
	ADF_neumannBC *self = _self;
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	setInputs(self);
	SUB(7, 4, 3)
	SUB(8, 5, 3)
	SUB(9, 7, 8)
	MUL(10, 8, 9)
	DIV(11, 7, 10)
	NEG(12, 11)
	DIV(13, 8, 7)
	CONST(14, 2.0000000000e+00)
	POW(15, 13, 14)
	MUL(16, 12, 15)
	NEG(17, 16)
	SUB(18, 17, 11)
	MUL(19, 16, 1)
	SUB(20, 6, 19)
	MUL(21, 11, 2)
	SUB(22, 20, 21)
	MUL(23, 18, 0)
	SUB(24, 22, 23)
	EQUAL(25, 24)
	getOutputs(self, 26);
	#ifndef DISABLE_DERIVS
	updateAllDerivs(self, 26);
	#endif
}

static void calculateDerivatives(ADF_neumannBC *self)
{
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	D_EQUAL(25, 24)
	D_SUB(24, 22, 23)
	D_MUL(23, 18, 0)
	D_SUB(22, 20, 21)
	D_MUL(21, 11, 2)
	D_SUB(20, 6, 19)
	D_MUL(19, 16, 1)
	D_SUB(18, 17, 11)
	D_NEG(17, 16)
	D_MUL(16, 12, 15)
	D_POW(15, 13, 14)
	D_DIV(13, 8, 7)
	D_NEG(12, 11)
	D_DIV(11, 7, 10)
	D_MUL(10, 8, 9)
	D_SUB(9, 7, 8)
	D_SUB(8, 5, 3)
	D_SUB(7, 4, 3)
}

#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/undefOps.h"

static void updateDerivs(ADF_neumannBC *self, VarAD *output)
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

static void updateAllDerivs(ADF_neumannBC *self, int size)
{
	int iOutput = size-1;
	for(int j=0; j>=0; j--)
	{
		for(int iVar=0; iVar<size; iVar++) self->___psi[iVar] = 0.0;
		VarAD *output = self->R_phi+j;
		self->___psi[iOutput] = 1.0; iOutput--;
		calculateDerivatives(self);
		updateDerivs(self, output);
	}
}

static void setInputs(ADF_neumannBC *self)
{
	int iInput = 0;
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->phi_0[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->phi_1[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->phi_2[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->y_b[i]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->y_1[i]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->y_2[i]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->value[i]; iInput++;
	}
}

static void getOutputs(ADF_neumannBC *self, int size)
{
	int iOutput = size-1;
	for(int i=0; i>=0; i--)
	{
		self->R_phi[i].data = self->___phi[iOutput]; iOutput--;
	}
}

