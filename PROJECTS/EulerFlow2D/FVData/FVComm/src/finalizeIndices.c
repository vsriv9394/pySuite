#include "../FVComm.h"

void finalizeIndices__FVComm
(
    void *_self
)
{
    FVComm *self  = _self;
    self->iIndices = calloc(self->iDispls[self->mpi_size], sizeof(int));
    self->iBuffer  = calloc(self->iDispls[self->mpi_size], sizeof(double)*9);
    self->eBuffer  = calloc(self->eDispls[self->mpi_size], sizeof(double)*9);

    MPI_Alltoallv
    (
        self->eIndices, self->eSizes, self->eDispls, MPI_INT,
        self->iIndices, self->iSizes, self->iDispls, MPI_INT, self->mpi_comm
    );
}