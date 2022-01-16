#ifndef ADF_dirichiletBC_h
#define ADF_dirichiletBC_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "/home/vsriv/codes/pySuite/pyad/VarAD/VarAD.h"
#include "/home/vsriv/codes/pySuite/pyad/JacAD/JacAD.h"
//INCLUDES_END

typedef struct
{
	double ___phi[4];
	double ___psi[4];
	VarAD *phi;
	double *value;
	VarAD *R_phi;
}
ADF_dirichiletBC;

void init__ADF_dirichiletBC(void *_self);
void calculate__ADF_dirichiletBC(void *_self);
void setup__ADF_dirichiletBC(void *_self);
void setVars__ADF_dirichiletBC(void *_self, void *phi, void *value, void *R_phi);

#endif
