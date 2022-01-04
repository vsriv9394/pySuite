#include "../FVComm.h"

void finalizeSizes__FVComm
(
    void *_self
)
{
    FVComm *self  = _self;
    self->iSizes  = calloc(self->mpi_size,   sizeof(int));
    self->iDispls = calloc(self->mpi_size+1, sizeof(int));
    self->eDispls = calloc(self->mpi_size+1, sizeof(int));

    MPI_Alltoall(self->eSizes, 1, MPI_INT, self->iSizes, 1, MPI_INT, self->mpi_comm);

    self->iDispls[0] = 0;
    self->eDispls[0] = 0;

    for(int i=0; i<self->mpi_size; i++)
    {
        self->iDispls[i+1] = self->iDispls[i] + self->iSizes[i];
        self->eDispls[i+1] = self->eDispls[i] + self->eSizes[i];
    }
}