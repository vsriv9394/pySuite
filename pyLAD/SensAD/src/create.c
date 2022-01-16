#include "../SensAD.h"

#define false 0

void create__SensAD
(
    void   *_self,
    void   *arrayAD,
    int    *indices,
    double *entries,
    int     naturalIndexing,
    int     nElems,
    int     elemSize
)
{
    SensAD *self = _self;
    self->arrayAD = arrayAD;
    
    if(indices!=NULL)
    {
        self->indices = indices;
    }
    else
    {
        if(!naturalIndexing)
        {
            self->indicesIsACopy = false;
            self->indices = calloc(nElems, sizeof(int));
        }
    }

    if(entries!=NULL)
    {
        self->entries = entries;
    }
    else
    {
        self->entriesIsACopy = false;
        self->entries = calloc(nElems*elemSize, sizeof(double));
    }
}

#undef false
