#include "../ADF_deriv2.h"

void init__ADF_deriv2
(
	void *_self
)
{
	ADF_deriv2* self = _self;
	self->uL = NULL;
	self->uC = NULL;
	self->uR = NULL;
	self->yL = NULL;
	self->yC = NULL;
	self->yR = NULL;
	self->d2udy2 = NULL;
}
