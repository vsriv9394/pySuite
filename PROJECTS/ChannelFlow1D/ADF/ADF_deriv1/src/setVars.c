#include "../ADF_deriv1.h"

void setVars__ADF_deriv1
(
	void *_self,
	void *uL,
	void *uC,
	void *uR,
	void *yL,
	void *yC,
	void *yR,
	void *dudy
)
{
	ADF_deriv1* self = _self;
	self->uL = uL;
	self->uC = uC;
	self->uR = uR;
	self->yL = yL;
	self->yC = yC;
	self->yR = yR;
	self->dudy = dudy;
}
