#include "../ADF_residuals.h"

void setVars__ADF_residuals
(
	void *_self,
	void *phi,
	void *grad_phi,
	void *hess_phi,
	void *cb1,
	void *nu,
	void *dpdx,
	void *wallDist,
	void *R_phi
)
{
	ADF_residuals* self = _self;
	self->phi = phi;
	self->grad_phi = grad_phi;
	self->hess_phi = hess_phi;
	self->cb1 = cb1;
	self->nu = nu;
	self->dpdx = dpdx;
	self->wallDist = wallDist;
	self->R_phi = R_phi;
}
