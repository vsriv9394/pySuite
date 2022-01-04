#include "../FVComm.h"

void delete__FVComm
(
    void *_self
)
{
    FVComm *self = _self;
    if(self->iSizes==NULL)    free(self->iSizes);
    if(self->eSizes==NULL)    free(self->eSizes);
    if(self->iDispls==NULL)  free(self->iDispls);
    if(self->eDispls==NULL)  free(self->eDispls);
    if(self->iIndices==NULL) free(self->iIndices);
    if(self->eIndices==NULL) free(self->eIndices);
    if(self->iBuffer==NULL)  free(self->iBuffer);
    if(self->eBuffer==NULL)  free(self->eBuffer);
}