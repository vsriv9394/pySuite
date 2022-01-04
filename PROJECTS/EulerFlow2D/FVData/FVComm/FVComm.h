#ifndef FVComm_h
#define FVComm_h

#include "mpi.h"
#include <string.h>

#define meow MPI_COMM_WORLD

//INCLUDES_BEGIN
//INCLUDES_END

typedef struct
{
    MPI_Comm mpi_comm;
    int mpi_rank;
    int mpi_size;
    int *iSizes;
    int *eSizes;
    int *iDispls;
    int *eDispls;
    int *iIndices;
    int *eIndices;
    char *iBuffer;
    char *eBuffer;
}
FVComm;

void init__FVComm(void *_self);
void delete__FVComm(void *_self);
void setMpiComm__FVComm(void *_self, void *mpi_comm);
void initSizes__FVComm(void *_self);
void finalizeSizes__FVComm(void *_self);
void initIndices__FVComm(void *_self);
void finalizeIndices__FVComm(void *_self);
void syncForward__FVComm(void *_self, int elemSize);
void syncReverse__FVComm(void *_self, int elemSize);
void iGet__FVComm(void *_self, int index, int elemSize, void *elem);
void eGet__FVComm(void *_self, int index, int elemSize, void *elem);
void iSet__FVComm(void *_self, int index, int elemSize, void *elem);
void eSet__FVComm(void *_self, int index, int elemSize, void *elem);

#endif