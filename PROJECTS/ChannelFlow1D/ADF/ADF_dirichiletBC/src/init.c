#include "../ADF_dirichiletBC.h"

void init__ADF_dirichiletBC
(
	void *_self
)
{
	ADF_dirichiletBC* self = _self;
	self->phi = NULL;
	self->value = NULL;
	self->R_phi = NULL;
}
