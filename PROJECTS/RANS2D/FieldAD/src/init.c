#include "../FieldAD.h"

void init__FieldAD
(
    void *_self
)
{
    FieldAD *self = _self;
    self->size  = 0;
    self->eSize = 0;
    self->data  = NULL;
    init__DepListAD(&(self->depList));
}