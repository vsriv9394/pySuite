#include "../ADF_dirichiletBC.h"
#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/defineOps.h"

static void calculateDerivatives(ADF_dirichiletBC *self);
static void updateDerivs(ADF_dirichiletBC *self, VarAD *output);
static void updateAllDerivs(ADF_dirichiletBC *self, int size);
static void setInputs(ADF_dirichiletBC *self);
static void getOutputs(ADF_dirichiletBC *self, int size);

void calculate__ADF_dirichiletBC
(
	void *_self
)
{
	ADF_dirichiletBC *self = _self;
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	setInputs(self);
	SUB(2, 1, 0)
	EQUAL(3, 2)
	getOutputs(self, 4);
	#ifndef DISABLE_DERIVS
	updateAllDerivs(self, 4);
	#endif
}

static void calculateDerivatives(ADF_dirichiletBC *self)
{
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	D_EQUAL(3, 2)
	D_SUB(2, 1, 0)
}

#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/undefOps.h"

static void updateDerivs(ADF_dirichiletBC *self, VarAD *output)
{
	int iInput = 0;
	for(int i=0; i<1; i++)
	{
		output->depSens[iInput] = self->___psi[iInput]; iInput++;
	}
}

static void updateAllDerivs(ADF_dirichiletBC *self, int size)
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

static void setInputs(ADF_dirichiletBC *self)
{
	int iInput = 0;
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->phi[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->value[i]; iInput++;
	}
}

static void getOutputs(ADF_dirichiletBC *self, int size)
{
	int iOutput = size-1;
	for(int i=0; i>=0; i--)
	{
		self->R_phi[i].data = self->___phi[iOutput]; iOutput--;
	}
}

