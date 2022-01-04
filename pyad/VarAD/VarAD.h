#ifndef VarAD_h
#define VarAD_h
#pragma pack(1)

#include <stdlib.h>
#include <string.h>

//INCLUDES_BEGIN
//INCLUDES_END

typedef struct
{
    double data;
    int nDeps;
    void **depPtrs;
    double *depSens;
}
VarAD;

void init__VarAD(void *_self);
void delete__VarAD(void *_self);
void calculateLinear__VarAD(void *_self);
void setupDeps__VarAD(void *_self, int nDeps, void **depPtrs);

#endif