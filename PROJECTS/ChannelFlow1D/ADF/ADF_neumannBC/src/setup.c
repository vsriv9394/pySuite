#include "../ADF_neumannBC.h"

void setup__ADF_neumannBC
(
	void *_self
)
{
	ADF_neumannBC* self = _self;

	void *ptrToDep[3]; int iInput = 0;

	for(int i=0; i<1; i++)
		ptrToDep[iInput++] = (void*)(self->phi_0+i);

	for(int i=0; i<1; i++)
		ptrToDep[iInput++] = (void*)(self->phi_1+i);

	for(int i=0; i<1; i++)
		ptrToDep[iInput++] = (void*)(self->phi_2+i);

	for(int i=0; i<1; i++)
		setupDeps__VarAD(self->R_phi+i, 3, ptrToDep);

}
