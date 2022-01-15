#ifndef JacMatAD_h
#define JacMatAD_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "../FieldAD/FieldAD.h"
//INCLUDES_END

typedef struct
{
    int nRows;
    int nCols;
    int *offsets;
    int *colIds;
    double *elems;
    FieldAD *inputs;
    FieldAD *outputs;
}
JacMatAD;

void init__JacMatAD(void *_self);
void delete__JacMatAD(void *_self);
void create__JacMatAD(void *_self, FieldAD *inputs, FieldAD *outputs);

#endif