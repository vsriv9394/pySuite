#include "../ADF_residuals.h"

void setup__ADF_residuals
(
	void *_self
)
{
	ADF_residuals* self = _self;

	void *ptrToDep[7]; int iInput = 0;

	for(int i=0; i<2; i++)
		ptrToDep[iInput++] = (void*)(self->phi+i);

	for(int i=0; i<2; i++)
		ptrToDep[iInput++] = (void*)(self->grad_phi+i);

	for(int i=0; i<2; i++)
		ptrToDep[iInput++] = (void*)(self->hess_phi+i);

	for(int i=0; i<1; i++)
		ptrToDep[iInput++] = (void*)(self->cb1+i);

	for(int i=0; i<2; i++)
		setupDeps__VarAD(self->R_phi+i, 7, ptrToDep);

}
