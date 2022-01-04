#include "../FVComm.h"

void setMpiComm__FVComm
(
    void *_self,
    void *mpi_comm
)
{
    FVComm *self = _self;
    self->mpi_comm = ((MPI_Comm*)(mpi_comm))[0];
    MPI_Comm_size(self->mpi_comm, &self->mpi_size);
    MPI_Comm_rank(self->mpi_comm, &self->mpi_comm);
}