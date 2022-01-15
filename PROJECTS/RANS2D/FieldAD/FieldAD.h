#ifndef FieldAD_h
#define FieldAD_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "DepListAD/DepListAD.h"
//INCLUDES_END

typedef struct
{
    int size;
    int eSize;
    double *data;
    DepListAD depList;
}
FieldAD;

void init__FieldAD(void *_self);
void delete__FieldAD(void *_self);
void create__FieldAD(void *_self, int size, int eSize);
void addDep__FieldAD(void *_self, void *ptr, int *conn, double *sens);

#endif