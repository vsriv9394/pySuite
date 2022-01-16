#include "../JacobianAD.h"

static int *_buffer;
static int _bufSize;

#include "utils.h"

static void registerDeps(JacobianAD *self, ArrayAD *X, int ind);

void create__JacobianAD
(
    void *_self,
    ArrayAD *outputs,
    ArrayAD *inputs
)
{
    JacobianAD *self = _self;

    //====================================================================
    // Setup stuff
    //====================================================================
    
    self->outputs = outputs;
    self->M = outputs->shape[0];
    self->m = outputs->eSize;
    
    self->inputs = inputs;
    self->N = inputs->shape[0];
    self->n = inputs->eSize;
    
    _buffer = calloc(self->N, sizeof(int));

    //====================================================================
    // Setup offsets
    //====================================================================

    self->offsets = calloc(self->M+1, sizeof(int));
    self->offsets[0] = 0;    

    for(int iOutput=0; iOutput<self->M; iOutput++)
    {
        _bufSize = 0;
        registerDeps(self, outputs, iOutput);
        self->offsets[iOutput+1] = self->offsets[iOutput] + _bufSize;
    }

    //====================================================================
    // Setup colIds
    //====================================================================

    self->iBlocks = calloc(self->offsets[self->M], sizeof(int));

    for(int iOutput=0; iOutput<self->M; iOutput++)
    {
        _bufSize = 0;
        registerDeps(self, outputs, iOutput);
        int offset = self->offsets[iOutput];
        for(int k=0; k<_bufSize; k++)
            self->iBlocks[offset+k] = _buffer[k];
    }

    //====================================================================
    // Allocate elements
    //====================================================================

    self->entries = calloc(self->offsets[self->M]*self->m*self->n, sizeof(double));

    free(_buffer);
}

static void registerDeps(JacobianAD *self, ArrayAD *X, int ind)
{
    if(X==self->inputs)
    {
        if(find(ind, _buffer, _bufSize) == -1)
        {
            _buffer[_bufSize++] = ind;
            endSort(_buffer, _bufSize);
        }
    }
    
    else for(int iDep=0; iDep<X->nDeps; iDep++)
    {
        int depInd = (X->deps[iDep].indices==NULL) ? ind : X->deps[iDep].indices[ind];
        registerDeps(self, X->deps[iDep].arrayAD, depInd);
    }
}
