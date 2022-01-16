#include "../ADF_residuals.h"
#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/defineOps.h"

static void calculateDerivatives(ADF_residuals *self);
static void updateDerivs(ADF_residuals *self, VarAD *output);
static void updateAllDerivs(ADF_residuals *self, int size);
static void setInputs(ADF_residuals *self);
static void getOutputs(ADF_residuals *self, int size);

void calculate__ADF_residuals
(
	void *_self
)
{
	ADF_residuals *self = _self;
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	setInputs(self);
	NEG(10, 8)
	MUL(11, 7, 4)
	ADD(12, 10, 11)
	DIV(13, 1, 7)
	CONST(14, 3.0000000000e+00)
	POW(15, 13, 14)
	CONST(16, 3.5791100000e+02)
	ADD(17, 15, 16)
	DIV(18, 15, 17)
	MUL(19, 18, 1)
	MUL(20, 19, 4)
	ADD(21, 12, 20)
	DIV(22, 14, 13)
	MUL(23, 22, 18)
	CONST(24, 1.0000000000e+00)
	SUB(25, 24, 18)
	MUL(26, 23, 25)
	DIV(27, 3, 7)
	MUL(28, 26, 27)
	MUL(29, 28, 1)
	MUL(30, 18, 3)
	ADD(31, 29, 30)
	MUL(32, 31, 2)
	ADD(33, 21, 32)
	CONST(34, 4.1000000000e-01)
	MUL(35, 34, 9)
	CONST(36, 2.0000000000e+00)
	POW(37, 35, 36)
	DIV(38, 1, 37)
	MUL(39, 13, 18)
	ADD(40, 24, 39)
	DIV(41, 13, 40)
	SUB(42, 24, 41)
	MUL(43, 38, 42)
	ADD(44, 2, 43)
	MUL(45, 6, 44)
	MUL(46, 45, 1)
	CONST(47, 1.6810000000e-01)
	DIV(48, 6, 47)
	CONST(49, 2.4330000000e+00)
	ADD(50, 48, 49)
	DIV(51, 38, 44)
	CONST(52, 1.0000000000e+01)
	FMIN(53, 51, 52)
	CONST(54, 6.0000000000e+00)
	POW(55, 53, 54)
	SUB(56, 55, 53)
	CONST(57, 3.0000000000e-01)
	MUL(58, 57, 56)
	ADD(59, 53, 58)
	POW(60, 59, 54)
	CONST(61, 6.4000000000e+01)
	ADD(62, 60, 61)
	CONST(63, 6.5000000000e+01)
	DIV(64, 63, 62)
	CONST(65, 1.6666666667e-01)
	POW(66, 64, 65)
	MUL(67, 59, 66)
	MUL(68, 50, 67)
	DIV(69, 1, 9)
	POW(70, 69, 36)
	MUL(71, 68, 70)
	SUB(72, 46, 71)
	ADD(73, 7, 1)
	CONST(74, 1.5000000000e+00)
	MUL(75, 74, 73)
	MUL(76, 75, 5)
	ADD(77, 72, 76)
	MUL(78, 49, 3)
	MUL(79, 78, 3)
	ADD(80, 77, 79)
	EQUAL(81, 33)
	EQUAL(82, 80)
	getOutputs(self, 83);
	#ifndef DISABLE_DERIVS
	updateAllDerivs(self, 83);
	#endif
}

static void calculateDerivatives(ADF_residuals *self)
{
	double *___psi = self->___psi;
	double *___phi = self->___phi;
	D_EQUAL(82, 80)
	D_EQUAL(81, 33)
	D_ADD(80, 77, 79)
	D_MUL(79, 78, 3)
	D_MUL(78, 49, 3)
	D_ADD(77, 72, 76)
	D_MUL(76, 75, 5)
	D_MUL(75, 74, 73)
	D_ADD(73, 7, 1)
	D_SUB(72, 46, 71)
	D_MUL(71, 68, 70)
	D_POW(70, 69, 36)
	D_DIV(69, 1, 9)
	D_MUL(68, 50, 67)
	D_MUL(67, 59, 66)
	D_POW(66, 64, 65)
	D_DIV(64, 63, 62)
	D_ADD(62, 60, 61)
	D_POW(60, 59, 54)
	D_ADD(59, 53, 58)
	D_MUL(58, 57, 56)
	D_SUB(56, 55, 53)
	D_POW(55, 53, 54)
	D_FMIN(53, 51, 52)
	D_DIV(51, 38, 44)
	D_ADD(50, 48, 49)
	D_DIV(48, 6, 47)
	D_MUL(46, 45, 1)
	D_MUL(45, 6, 44)
	D_ADD(44, 2, 43)
	D_MUL(43, 38, 42)
	D_SUB(42, 24, 41)
	D_DIV(41, 13, 40)
	D_ADD(40, 24, 39)
	D_MUL(39, 13, 18)
	D_DIV(38, 1, 37)
	D_POW(37, 35, 36)
	D_MUL(35, 34, 9)
	D_ADD(33, 21, 32)
	D_MUL(32, 31, 2)
	D_ADD(31, 29, 30)
	D_MUL(30, 18, 3)
	D_MUL(29, 28, 1)
	D_MUL(28, 26, 27)
	D_DIV(27, 3, 7)
	D_MUL(26, 23, 25)
	D_SUB(25, 24, 18)
	D_MUL(23, 22, 18)
	D_DIV(22, 14, 13)
	D_ADD(21, 12, 20)
	D_MUL(20, 19, 4)
	D_MUL(19, 18, 1)
	D_DIV(18, 15, 17)
	D_ADD(17, 15, 16)
	D_POW(15, 13, 14)
	D_DIV(13, 1, 7)
	D_ADD(12, 10, 11)
	D_MUL(11, 7, 4)
	D_NEG(10, 8)
}

#include "/home/vsriv/codes/pySuite/pyad/pyAD/headers/undefOps.h"

static void updateDerivs(ADF_residuals *self, VarAD *output)
{
	int iInput = 0;
	for(int i=0; i<2; i++)
	{
		output->depSens[iInput] = self->___psi[iInput]; iInput++;
	}
	for(int i=0; i<2; i++)
	{
		output->depSens[iInput] = self->___psi[iInput]; iInput++;
	}
	for(int i=0; i<2; i++)
	{
		output->depSens[iInput] = self->___psi[iInput]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		output->depSens[iInput] = self->___psi[iInput]; iInput++;
	}
}

static void updateAllDerivs(ADF_residuals *self, int size)
{
	int iOutput = size-1;
	for(int j=1; j>=0; j--)
	{
		for(int iVar=0; iVar<size; iVar++) self->___psi[iVar] = 0.0;
		VarAD *output = self->R_phi+j;
		self->___psi[iOutput] = 1.0; iOutput--;
		calculateDerivatives(self);
		updateDerivs(self, output);
	}
}

static void setInputs(ADF_residuals *self)
{
	int iInput = 0;
	for(int i=0; i<2; i++)
	{
		self->___phi[iInput] = self->phi[i].data; iInput++;
	}
	for(int i=0; i<2; i++)
	{
		self->___phi[iInput] = self->grad_phi[i].data; iInput++;
	}
	for(int i=0; i<2; i++)
	{
		self->___phi[iInput] = self->hess_phi[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->cb1[i].data; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->nu[i]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->dpdx[i]; iInput++;
	}
	for(int i=0; i<1; i++)
	{
		self->___phi[iInput] = self->wallDist[i]; iInput++;
	}
}

static void getOutputs(ADF_residuals *self, int size)
{
	int iOutput = size-1;
	for(int i=1; i>=0; i--)
	{
		self->R_phi[i].data = self->___phi[iOutput]; iOutput--;
	}
}

