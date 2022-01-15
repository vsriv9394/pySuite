#ifndef FVFaceContainer_h
#define FVFaceContainer_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "../../../../pyad/VarAD/VarAD.h"
//INCLUDES_END

typedef struct
{
    int    size;
    int    *nodes;
    int    *cells;
    double *normal;
    double *center;
    double *lDisp;
    double *rDisp;
    VarAD  *fluxes;
}
FVFaceContainer;

void init__FVFaceContainer(void *_self);
void delete__FVFaceContainer(void *_self);
void create__FVFaceContainer(void *_self, int nDim, int nStates);

#endif