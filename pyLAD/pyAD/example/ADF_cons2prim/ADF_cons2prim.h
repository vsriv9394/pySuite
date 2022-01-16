#ifndef ADF_cons2prim_h
#define ADF_cons2prim_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/ArrayAD/ArrayAD.h"
#include "/home/vsriv/codes/pySuite/PROJECTS/RANS2D/AutoDiff/JacobianAD/JacobianAD.h"
//INCLUDES_END

typedef struct
{
	double ___phi[25];
	double ___psi[25];
	double *Uc;
	double *R;
	double *gamma;
	double *Up;
	double *d_Up__d_Uc;
}
ADF_cons2prim;

void init__ADF_cons2prim(void *_self);
void calculate__ADF_cons2prim(void *_self);

#endif
