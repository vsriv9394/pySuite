#include "../ArrayAD.h"

void calculateLinear__ArrayAD
(
    void *_self
)
{
    ArrayAD *self = _self;

    for(int I=0; I<self->shape[0]; I++)
        for(int i=0; i<self->eSize; i++)
            self->data[I*self->eSize+i] = 0.0;

    for(int iDep=0; iDep<self->nDeps; iDep++)
    {
        ArrayAD *X    = self->deps[iDep].arrayAD;
        int     *ind  = self->deps[iDep].indices;
        double  *sens = self->deps[iDep].entries;
        
        for(int I=0; I<self->shape[0]; I++)
            for(int i=0; i<self->eSize; i++)
                for(int j=0; j<X->eSize; j++)
                    self->data[I*self->eSize+i] += \
                    X->data[ind[i]*X->eSize+j] *
                    sens[(I*self->eSize+i)*X->eSize+j];
    }
}
