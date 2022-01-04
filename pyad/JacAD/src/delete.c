#include "../JacAD.h"

void delete__JacAD
(
    void *_self
)
{
    JacAD *self = _self;
    if(self->offsets!=NULL) free(self->offsets);
    if(self->colIds!=NULL)  free(self->colIds);
    if(self->elems!=NULL)   free(self->elems);
    init__JacAD(_self);
}