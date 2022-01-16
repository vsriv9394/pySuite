#include "../ADF_residuals.h"

void init__ADF_residuals
(
	void *_self
)
{
	ADF_residuals* self = _self;
	self->phi = NULL;
	self->grad_phi = NULL;
	self->hess_phi = NULL;
	self->cb1 = NULL;
	self->nu = NULL;
	self->dpdx = NULL;
	self->wallDist = NULL;
	self->R_phi = NULL;
}
