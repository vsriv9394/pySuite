#include "../VarAD.h"

void calculateLinear__VarAD
(
    void *_self
)
{
    VarAD *self = _self;
    
    self->data = 0.0;

    for(int i=0; i<self->nDeps; i++)
    {
        VarAD *other = self->depPtrs[i];
        self->data += other->data * self->depSens[i];
    }
}