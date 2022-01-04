#include "../Mesh1D.h"

void init__Mesh1D
(
    void *_self
)
{
    Mesh1D *self = _self;
    self->nNodes = 0;
    self->x = NULL;
}
