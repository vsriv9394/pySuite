#include "../JacMatAD.h"

void init__JacMatAD
(
    void *_self
)
{
    JacMatAD *self = _self;
    self->nRows = 0;
    self->nCols = 0;
    self->offsets = NULL;
    self->colIds = NULL;
    self->elems = NULL;
    self->inputs = NULL;
    self->outputs = NULL;
}