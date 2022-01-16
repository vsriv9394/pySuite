#ifndef ADF_neumannBC_h
#define ADF_neumannBC_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "/home/vsriv/codes/pySuite/pyad/VarAD/VarAD.h"
#include "/home/vsriv/codes/pySuite/pyad/JacAD/JacAD.h"
//INCLUDES_END

typedef struct
{
	double ___phi[26];
	double ___psi[26];
	VarAD *phi_0;
	VarAD *phi_1;
	VarAD *phi_2;
	double *y_b;
	double *y_1;
	double *y_2;
	double *value;
	VarAD *R_phi;
}
ADF_neumannBC;

void init__ADF_neumannBC(void *_self);
void calculate__ADF_neumannBC(void *_self);
void setup__ADF_neumannBC(void *_self);
void setVars__ADF_neumannBC(void *_self, void *phi_0, void *phi_1, void *phi_2, void *y_b, void *y_1, void *y_2, void *value, void *R_phi);

#endif
