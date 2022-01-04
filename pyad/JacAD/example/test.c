#include <stdio.h>
#include "../JacAD.h"

int main()
{
    VarAD x[2], y[2], z[2];
    for(int i=0; i<2; i++) init__VarAD(x+i);
    for(int i=0; i<2; i++) init__VarAD(y+i);
    for(int i=0; i<2; i++) init__VarAD(z+i);

    void *yBuf[] = {x, x+1};
    void *zBuf[] = {y, y+1};
    for(int i=0; i<2; i++) setupDeps__VarAD(y+i, 2, yBuf);
    for(int i=0; i<2; i++) setupDeps__VarAD(z+i, 2, zBuf);

    JacAD jac; init__JacAD(&jac); create__JacAD(&jac, 2, 2, x, z);
    
    z[0].depSens[0] = 1;
    z[0].depSens[1] = 2;
    z[1].depSens[0] = 3;
    z[1].depSens[1] = 4;

    y[0].depSens[0] = 5;
    y[0].depSens[1] = 6;
    y[1].depSens[0] = 7;
    y[1].depSens[1] = 8;
    
    calculate__JacAD(&jac);

    for(int i=0; i<jac.nRows; i++)
        for(int j=jac.offsets[i]; j<jac.offsets[i+1]; j++)
            printf("%d %d %le\n", i, jac.colIds[j], jac.elems[j]);
    
    delete__JacAD(&jac);

    for(int i=0; i<2; i++) delete__VarAD(z+i);
    for(int i=0; i<2; i++) delete__VarAD(y+i);
    for(int i=0; i<2; i++) delete__VarAD(x+i);
}