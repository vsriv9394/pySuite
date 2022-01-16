#ifndef ADF_deriv2_h
#define ADF_deriv2_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "/home/vsriv/codes/pySuite/pyad/VarAD/VarAD.h"
#include "/home/vsriv/codes/pySuite/pyad/JacAD/JacAD.h"
//INCLUDES_END

typedef struct
{
	double ___phi[18];
	double ___psi[18];
	VarAD *uL;
	VarAD *uC;
	VarAD *uR;
	double *yL;
	double *yC;
	double *yR;
	VarAD *d2udy2;
}
ADF_deriv2;

void init__ADF_deriv2(void *_self);
void calculate__ADF_deriv2(void *_self);
void setup__ADF_deriv2(void *_self);
void setVars__ADF_deriv2(void *_self, void *uL, void *uC, void *uR, void *yL, void *yC, void *yR, void *d2udy2);

#endif
