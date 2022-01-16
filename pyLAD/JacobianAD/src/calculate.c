#include "../JacobianAD.h"
#include "utils.h"

static void calculate(JacobianAD *self, ArrayAD *X, int i, int j, int iRow, int jRow, double sens);

void calculate__JacobianAD
(
    void *_self
)
{
    JacobianAD *self = _self;
    
    int iEntry = 0;
    for(int iBlock=0; iBlock<self->offsets[self->M]; iBlock++)
        for(int i=0; i<self->m; i++) for(int j=0; j<self->n; j++)
            self->entries[iEntry++] = 0.0;
    
    for(int iOutput=0; iOutput<self->M; iOutput++)
        for(int jOutput=0; jOutput<self->m; jOutput++)
            calculate(self, self->outputs, iOutput, jOutput, iOutput, jOutput, 1.0);
}

static void calculate(JacobianAD *self, ArrayAD *X, int i, int j, int iRow, int jRow, double sens)
{
    if(X==self->inputs)
    {
        int rowOffset  = self->offsets[iRow];
        int nRowBlocks = self->offsets[iRow+1] - rowOffset;
        int iRowBlock  = find(i, self->iBlocks + rowOffset, nRowBlocks);
        int index      = ((rowOffset+iRowBlock) * self->m + jRow) * self->n + j;
        self->entries[index] += sens;
    }
    else for(int iDep=0; iDep<X->nDeps; iDep++)
    {
        ArrayAD *Y = X->deps[iDep].arrayAD;
        int ii = (X->deps[iDep].indices==NULL) ? i : X->deps[iDep].indices[i];

        for(int jj=0; jj<Y->eSize; jj++)
        {
            double dSens = X->deps[iDep].entries[(i*X->eSize + j) * Y->eSize + jj];
            calculate(self, Y, ii, jj, iRow, jRow, sens * dSens);
        }
    }
}
