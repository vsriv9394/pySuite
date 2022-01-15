#ifndef FVAugContainer_h
#define FVAugContainer_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "../../../../pyad/VarAD/VarAD.h"
//INCLUDES_END

typedef struct
{
    int    size;
    int    *nFeatures;
    char   **names;
    int    **alloc;
    double **linearizedAug;
    VarAD  ***features;
}
FVAugContainer;

#endif