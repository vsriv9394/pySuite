#include "../ADF_deriv2.h"

void setup__ADF_deriv2
(
	void *_self
)
{
	ADF_deriv2* self = _self;

	void *ptrToDep[3]; int iInput = 0;

	for(int i=0; i<1; i++)
		ptrToDep[iInput++] = (void*)(self->uL+i);

	for(int i=0; i<1; i++)
		ptrToDep[iInput++] = (void*)(self->uC+i);

	for(int i=0; i<1; i++)
		ptrToDep[iInput++] = (void*)(self->uR+i);

	for(int i=0; i<1; i++)
		setupDeps__VarAD(self->d2udy2+i, 3, ptrToDep);

}
