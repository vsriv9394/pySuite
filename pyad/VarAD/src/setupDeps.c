#include "../VarAD.h"

void setupDeps__VarAD
(
    void *_self,
    int nDeps,
    void **depPtrs
)
{
    VarAD *self = _self;
    self->nDeps = nDeps;
    self->depPtrs = calloc(nDeps, sizeof(void*));
    self->depSens = calloc(nDeps, sizeof(double));
    memcpy(self->depPtrs, depPtrs, nDeps*sizeof(void*));
}