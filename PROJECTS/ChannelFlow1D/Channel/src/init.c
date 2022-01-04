#include "../Channel.h"

void init__Channel
(
    void *_self
)
{
    Channel *self = _self;
    self->nStates = 0;
    self->nPoints = 0;
    self->nu = 0.0;
    self->dpdx = 0.0;
    self->wallBC = NULL;
    self->y = NULL;
    self->U_values = NULL;
    self->R_values = NULL;
    self->U = NULL;
    self->R = NULL;
    init__JacAD(&(self->J));
}