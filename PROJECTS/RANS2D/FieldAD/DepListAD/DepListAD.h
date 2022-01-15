#ifndef DepListAD_h
#define DepListAD_h
#pragma pack(1)

#include <stdlib.h>

//INCLUDES_BEGIN
//INCLUDES_END

typedef struct
{
    void *next;
    void *ptr;
    int *conn;
    double *sens;
    int connIsACopy;
    int sensIsACopy;
}
DepListAD;

void init__DepListAD(void *_self);
void delete__DepListAD(void *_self);
void create__DepListAD(void *_self, void *ptr, int *conn, double *sens);

#endif