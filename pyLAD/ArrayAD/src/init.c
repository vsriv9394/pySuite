#include "../ArrayAD.h"

void init__ArrayAD
(
    void *_self
)
{
    ArrayAD *self = _self;
    self->shape[0] =    0;
    self->shape[1] =    1;
    self->shape[2] =    1;
    self->shape[3] =    1;
    self->eSize    =    1;
    self->nDeps    =    0;
    self->data     = NULL;
    self->deps     = NULL;
}
