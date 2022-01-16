#include "../ArrayAD.h"

void setDep__ArrayAD
(
    void   *_self,
    int    iDep,
    void   *arrayAD,
    int    *indices,
    double *entries,
    int naturalIndexing
)
{
    ArrayAD *self = _self;
    ArrayAD *other = arrayAD;
    
    int nElems = self->shape[0];
    
    int elemSize = self->eSize * other->eSize;
    
    create__SensAD(
        self->deps + iDep,
        arrayAD, indices, entries,
        naturalIndexing, nElems, elemSize
    );
}
