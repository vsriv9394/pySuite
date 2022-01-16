#include "../ADF_deriv1.h"

void init__ADF_deriv1
(
	void *_self
)
{
	ADF_deriv1* self = _self;
	self->uL = NULL;
	self->uC = NULL;
	self->uR = NULL;
	self->yL = NULL;
	self->yC = NULL;
	self->yR = NULL;
	self->dudy = NULL;
}
