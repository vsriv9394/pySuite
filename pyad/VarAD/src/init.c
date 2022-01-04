#include "../VarAD.h"

void init__VarAD
(
    void *_self
)
{
    VarAD *self = _self;
    self->data = 0.0;
    self->nDeps = 0;
    self->depPtrs = NULL;
    self->depSens = NULL;
}