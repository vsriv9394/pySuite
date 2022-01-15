#include "../FieldAD.h"

void create__DepListAD
(
    void *_self,
    int size,
    int eSize
)
{
    FieldAD *self = _self;
    self->size = size;
    self->eSize = eSize;
    self->data = calloc(size*eSize, sizeof(double));
}