#include "../FVComm.h"

void syncForward__FVComm
(
    void *_self,
    int elemSize
)
{
    FVComm *self = _self;

    for(int i=0; i<self->mpi_size; i++)
    {
        self->iSizes[i] *= elemSize;
        self->iDispls[i] *= elemSize;
        self->eSizes[i] *= elemSize;
        self->eDispls[i] *= elemSize;
    }

    MPI_Alltoallv
    (
        self->iBuffer, self->iSizes, self->iDispls, MPI_BYTE,
        self->eBuffer, self->eSizes, self->eDispls, MPI_BYTE, self->mpi_comm
    );

    for(int i=0; i<self->mpi_size; i++)
    {
        self->iSizes[i] /= elemSize;
        self->iDispls[i] /= elemSize;
        self->eSizes[i] /= elemSize;
        self->eDispls[i] /= elemSize;
    }
}