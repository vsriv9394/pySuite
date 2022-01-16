#include "../ADF_deriv2.h"

void setVars__ADF_deriv2
(
	void *_self,
	void *uL,
	void *uC,
	void *uR,
	void *yL,
	void *yC,
	void *yR,
	void *d2udy2
)
{
	ADF_deriv2* self = _self;
	self->uL = uL;
	self->uC = uC;
	self->uR = uR;
	self->yL = yL;
	self->yC = yC;
	self->yR = yR;
	self->d2udy2 = d2udy2;
}
