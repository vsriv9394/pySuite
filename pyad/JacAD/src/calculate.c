#include "../JacAD.h"
#include <stdio.h>

static int find_index(int entry, int n, int *arr);
static void calcSens(JacAD *self, VarAD *var, int iOutput, double sens);

void calculate__JacAD
(
    void *_self
)
{
    JacAD *self = _self;
    for(int i=0; i<self->offsets[self->nRows]; i++) {
        self->elems[i] = 0.0;
    }
    for(int i=0; i<self->nRows; i++) {
        calcSens(self, self->outputs+i, i, 1.0);
    }
}

static void calcSens(JacAD *self, VarAD *var, int iOutput, double sens)
{
    int *O = self->offsets + iOutput; int *C = self->colIds + O[0];
    for(int i=0; i<var->nDeps; i++)
    {
        VarAD *depPtr = var->depPtrs[i];
        double depSens = var->depSens[i] * sens;
        unsigned long D = depPtr - self->inputs;
        if(D < self->nRows) self->elems[O[0]+find_index(D,O[1]-O[0],C)] += depSens;
        else calcSens(self, depPtr, iOutput, depSens);
    }
}

static int find_index(int entry, int n, int *arr)
{
    int nb2, nb2p1; int *arr_orig = arr;
    while(n>1)
    {
        nb2 = n>>1;
        if(arr[nb2]==entry) { arr+=nb2; break; }
        else if(arr[nb2]>entry) n=nb2;
        else { nb2p1=nb2+1; n-=nb2p1; arr+=nb2p1;  }
    }
    return (int)(arr-arr_orig);
}