#include "../ADF_neumannBC.h"

void init__ADF_neumannBC
(
	void *_self
)
{
	ADF_neumannBC* self = _self;
	self->phi_0 = NULL;
	self->phi_1 = NULL;
	self->phi_2 = NULL;
	self->y_b = NULL;
	self->y_1 = NULL;
	self->y_2 = NULL;
	self->value = NULL;
	self->R_phi = NULL;
}
