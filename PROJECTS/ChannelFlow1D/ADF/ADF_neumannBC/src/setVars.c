#include "../ADF_neumannBC.h"

void setVars__ADF_neumannBC
(
	void *_self,
	void *phi_0,
	void *phi_1,
	void *phi_2,
	void *y_b,
	void *y_1,
	void *y_2,
	void *value,
	void *R_phi
)
{
	ADF_neumannBC* self = _self;
	self->phi_0 = phi_0;
	self->phi_1 = phi_1;
	self->phi_2 = phi_2;
	self->y_b = y_b;
	self->y_1 = y_1;
	self->y_2 = y_2;
	self->value = value;
	self->R_phi = R_phi;
}
