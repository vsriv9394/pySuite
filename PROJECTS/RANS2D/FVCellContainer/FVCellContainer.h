#ifndef FVCellContainer_h
#define FVCellContainer_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "../FVAugContainer/FVAugContainer.h"
//INCLUDES_END

typedef struct
{
    int    size;
    int    *nodes;
    double *volume;
    double *center;
    VarAD  *states;
    VarAD  *U;
    VarAD  *gradU;
    VarAD  *residuals;
    VarAD  *observables;
    FVAugContainer augs;
}
FVCellContainer;

void init__FVCellContainer(void *_self);
void delete__FVCellContainer(void *_self);
void create__FVCellContainer(void *_self, int nDim, int nStates, int nObs);

#endif