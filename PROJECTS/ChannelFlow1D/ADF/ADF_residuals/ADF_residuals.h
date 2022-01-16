#ifndef ADF_residuals_h
#define ADF_residuals_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "/home/vsriv/codes/pySuite/pyad/VarAD/VarAD.h"
#include "/home/vsriv/codes/pySuite/pyad/JacAD/JacAD.h"
//INCLUDES_END

typedef struct
{
	double ___phi[83];
	double ___psi[83];
	VarAD *phi;
	VarAD *grad_phi;
	VarAD *hess_phi;
	VarAD *cb1;
	double *nu;
	double *dpdx;
	double *wallDist;
	VarAD *R_phi;
}
ADF_residuals;

void init__ADF_residuals(void *_self);
void calculate__ADF_residuals(void *_self);
void setup__ADF_residuals(void *_self);
void setVars__ADF_residuals(void *_self, void *phi, void *grad_phi, void *hess_phi, void *cb1, void *nu, void *dpdx, void *wallDist, void *R_phi);

#endif
