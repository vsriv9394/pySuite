#include "../ADF_dirichiletBC.h"

void setVars__ADF_dirichiletBC
(
	void *_self,
	void *phi,
	void *value,
	void *R_phi
)
{
	ADF_dirichiletBC* self = _self;
	self->phi = phi;
	self->value = value;
	self->R_phi = R_phi;
}
