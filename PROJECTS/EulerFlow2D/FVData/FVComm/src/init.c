#include "../FVComm.h"

void init__FVComm
(
    void *_self
)
{
    FVComm *self = _self;
    self->mpi_comm = MPI_COMM_WORLD;
    MPI_Comm_size(self->mpi_comm, &self->mpi_size);
    MPI_Comm_rank(self->mpi_comm, &self->mpi_comm);
    self->iSizes = NULL;
    self->eSizes = NULL;
    self->iDispls = NULL;
    self->eDispls = NULL;
    self->iIndices = NULL;
    self->eIndices = NULL;
    self->iBuffer = NULL;
    self->eBuffer = NULL;
}