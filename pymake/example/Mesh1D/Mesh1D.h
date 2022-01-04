#ifndef Mesh1D_h
#define Mesh1D_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//INCLUDES_BEGIN
//INCLUDES_END

typedef struct
{
    int nNodes;
    double *x;
}
Mesh1D;

void init__Mesh1D(void *_self);
void delete__Mesh1D(void *_self);
void create__Mesh1D(void *_self, int nNodes, double dx0, double xMin, double xMax);

#endif
