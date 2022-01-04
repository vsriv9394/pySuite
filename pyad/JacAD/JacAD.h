#ifndef JacAD_h
#define JacAD_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "../VarAD/VarAD.h"
//INCLUDES_END

// CSR format Jacobian matrix

typedef struct
{
    int nRows;
    int nCols;
    int *offsets;
    int *colIds;
    double *elems;
    VarAD *inputs;
    VarAD *outputs;
}
JacAD;

void init__JacAD(void *_self);
void delete__JacAD(void *_self);
void calculate__JacAD(void *_self);
void create__JacAD(void *_self, int nInputs, int nOutputs, VarAD *inputs, VarAD *outputs);

#endif
