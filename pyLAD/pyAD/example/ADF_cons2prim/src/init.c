#include "../ADF_cons2prim.h"

void init__ADF_cons2prim
(
	void *_self
)
{
	ADF_cons2prim* self = _self;
	self->Uc = NULL;
	self->R = NULL;
	self->gamma = NULL;
	self->Up = NULL;
	self->d_Up__d_Uc = NULL;
}
