#include "../SensAD.h"

#define false 0

void delete__SensAD
(
    void *_self
)
{
    SensAD *self = _self;
    if(self->arrayAD==NULL) free(self->arrayAD);
    if(self->indicesIsACopy==false) free(self->indices);
    if(self->entriesIsACopy==false) free(self->entries);
    init__SensAD(_self);
}

#undef false
