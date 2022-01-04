#include "../FVComm.h"

void initIndices__FVComm
(
    void *_self
)
{
    FVComm *self = _self;
    self->eIndices = calloc(self->eDispls[self->mpi_size], sizeof(int));
}