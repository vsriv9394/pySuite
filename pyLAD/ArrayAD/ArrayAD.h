#ifndef ArrayAD_h
#define ArrayAD_h
#pragma pack(1)

#include <stdio.h>
#include <stdlib.h>

//INCLUDES_BEGIN
#include "../SensAD/SensAD.h"
//INCLUDES_END

typedef struct
{
    int     shape[4];
    int     eSize;
    int     nDeps;
    double *data;
    SensAD *deps;
}
ArrayAD;

void init__ArrayAD(void *_self);
void delete__ArrayAD(void *_self);
void create__ArrayAD(void *_self);
void setNumDeps__ArrayAD(void *_self, int nDeps);
void setDep__ArrayAD(void *_self, int iDep, void *arrayAD, int *indices, double *entries, int naturalIndexing);
void calculateLinear__ArrayAD(void *_self);

#endif
