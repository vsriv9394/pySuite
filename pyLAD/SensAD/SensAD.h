#ifndef SensAD_h
#define SensAD_h
#pragma pack(1)

#include <stdlib.h>

//INCLUDES_BEGIN
//INCLUDES_END

typedef struct
{
    void   *arrayAD;
    int    *indices;
    double *entries;
    int     indicesIsACopy;
    int     entriesIsACopy;
}
SensAD;

void init__SensAD(void *_self);
void delete__SensAD(void *_self);
void create__SensAD(void *_self, void *arrayAD, int *indices, double *entries, int naturalIndexing, int nElems, int elemSize);

#endif
