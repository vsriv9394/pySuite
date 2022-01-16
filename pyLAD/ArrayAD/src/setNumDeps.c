#include "../ArrayAD.h"

void setNumDeps__ArrayAD
(
    void *_self,
    int nDeps
)
{
    ArrayAD *self = _self;
    
    self->nDeps = nDeps;
    self->deps  = calloc(nDeps, sizeof(ArrayAD));
    
    for(int iDep=0; iDep<self->nDeps; iDep++)
    {
        init__SensAD(self->deps + iDep);
    }
}
