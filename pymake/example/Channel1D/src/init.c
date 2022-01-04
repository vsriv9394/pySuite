#include "../Channel1D.h"

void init__Channel1D
(
    void *_self
)
{
    Channel1D *self = _self;
    init__Mesh1D(&(self->mesh));
    self->U = NULL;
    self->R = NULL;
}
