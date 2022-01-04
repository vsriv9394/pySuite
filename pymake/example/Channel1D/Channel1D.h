#ifndef Channel1D_h
#define Channel1D_h

#include <stdio.h>
#include <stdlib.h>

//INCLUDES_BEGIN
#include "../Mesh1D/Mesh1D.h"
//INCLUDES_END

typedef struct
{
    Mesh1D mesh;
    double (*U)[2];
    double (*R)[2];
}
Channel1D;

void init__Channel1D(void *_self);
void delete__Channel1D(void *_self);
void create__Channel1D(void *_self, int nNodes, double dx0, double xMin, double xMax);
void calculateResiduals__Channel1D(void *_self, double (*U)[2], double (*R)[2]);

#endif
