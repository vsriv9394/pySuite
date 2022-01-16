#include "../ADF_dirichiletBC.h"

void setup__ADF_dirichiletBC
(
	void *_self
)
{
	ADF_dirichiletBC* self = _self;

	void *ptrToDep[1]; int iInput = 0;

	for(int i=0; i<1; i++)
		ptrToDep[iInput++] = (void*)(self->phi+i);

	for(int i=0; i<1; i++)
		setupDeps__VarAD(self->R_phi+i, 1, ptrToDep);

}
