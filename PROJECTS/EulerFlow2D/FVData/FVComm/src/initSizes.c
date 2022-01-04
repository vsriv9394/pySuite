#include "../FVComm.h"

void initSizes__FVComm
(
    void *_self
)
{
    FVComm *self = _self;
    self->eSizes = calloc(self->mpi_size, sizeof(int));
}