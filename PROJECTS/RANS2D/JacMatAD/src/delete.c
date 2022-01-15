#include "../JacMatAD.h"

void delete__JacMatAD
(
    void *_self
)
{
    JacMatAD *self = _self;
    if(self->offsets!=NULL) free(self->offsets);
    if(self->colIds!=NULL) free(self->colIds);
    if(self->elems!=NULL) free(self->elems);
}