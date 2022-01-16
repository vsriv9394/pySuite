#include "../SensAD.h"

#define true 1

void init__SensAD
(
    void *_self
)
{
    SensAD *self = _self;
    self->arrayAD = NULL;
    self->indices = NULL;
    self->entries = NULL;
    self->indicesIsACopy = true;
    self->entriesIsACopy = true;
}

#undef true
