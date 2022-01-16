#include "../JacobianAD.h"

void init__JacobianAD
(
    void *_self
)
{
    JacobianAD *self = _self;
    self->M       = 0;
    self->N       = 0;
    self->m       = 0;
    self->n       = 0;
    self->offsets = NULL;
    self->iBlocks = NULL;
    self->entries = NULL;
    self->inputs  = NULL;
    self->outputs = NULL;
}
