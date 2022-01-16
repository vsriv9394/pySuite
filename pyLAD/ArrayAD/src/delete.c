#include "../ArrayAD.h"

void delete__ArrayAD
(
    void *_self
)
{
    ArrayAD *self = _self;

    if(self->data!=NULL) free(self->data);
    
    if(self->nDeps > 0)
    {
        for(int iDep=0; iDep<self->nDeps; iDep++)
        {
            delete__SensAD(self->deps + iDep);
        }

        free(self->deps);
    }

    init__ArrayAD(_self);
}
