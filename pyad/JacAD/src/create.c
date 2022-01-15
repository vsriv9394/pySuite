#include "../JacAD.h"
#include <stdio.h>

static int buffer[10000];
static int bufferCount;

static void registerDeps(JacAD *self, VarAD *var);
static void sort(int n, int *arr);

void create__JacAD
(
    void *_self,
    int nInputs,
    int nOutputs,
    VarAD *inputs,
    VarAD *outputs
)
{
    delete__JacAD(_self); JacAD *self = _self;
    self->inputs = inputs; self->outputs = outputs;
    self->nRows = nOutputs; self->nCols = nInputs;

    self->offsets = calloc(self->nRows+1, sizeof(int));
    self->offsets[0] = 0;

    for(int i=0; i<self->nRows; i++)
    {
        bufferCount = 0; registerDeps(self, self->outputs+i);
        self->offsets[i+1] = self->offsets[i] + bufferCount;
    }

    self->colIds = calloc(self->offsets[self->nRows], sizeof(int));

    for(int i=0; i<self->nRows; i++)
    {
        int offset = self->offsets[i]; bufferCount = 0;
        registerDeps(self, self->outputs+i);
        sort(bufferCount, buffer);
        for(int j=0; j<bufferCount; j++)
            self->colIds[offset+j] = buffer[j];
    }

    self->elems = calloc(self->offsets[self->nRows], sizeof(double));

    for(int i=0; i<self->offsets[self->nRows]; i++) self->elems[i] = 0.0;
}

static void sort(int n, int *arr)
{
    int sorted = 0; while(!sorted) {
        sorted = 1; int prev = arr[0]; for(int i=1; i<n; i++) {
            if(prev > arr[i]) { arr[i-1] = arr[i]; arr[i] = prev; sorted = 0; }
            else prev = arr[i];
        }
    }
}

static void registerDeps(JacAD *self, VarAD *var)
{
    for(int i=0; i<var->nDeps; i++)
    {
        VarAD *depPtr = var->depPtrs[i];
        unsigned long diff = depPtr - self->inputs;
        if(diff < self->nRows)
        {
            int exists = 0;
            for(int j=0; j<bufferCount; j++) if(buffer[j]==diff)
            { exists=1; break; } if(exists) continue;
            buffer[bufferCount++] = diff;
        }
        else registerDeps(self, depPtr);
    }
}
