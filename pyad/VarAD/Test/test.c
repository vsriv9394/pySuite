#include <stdio.h>
#include "../VarAD.h"

int main()
{
    VarAD x[2], y[2];
    
    for(int i=0; i<2; i++) init__VarAD(x+i);
    for(int i=0; i<2; i++) init__VarAD(y+i);

    printf("Meow1\n");

    void *deps[2] = {x, x+1};

    printf("Meow2\n");

    for(int i=0; i<2; i++) setupDeps__VarAD(y+i, 2, deps);

    printf("Meow3\n");

    y[0].depSens[0] = 1.0;
    y[0].depSens[1] = 2.0;
    y[1].depSens[0] = 3.0;
    y[1].depSens[1] = 4.0;

    printf("Meow4\n");

    x[0].data = 1;
    x[1].data = 2;

    printf("Meow5\n");

    for(int i=0; i<2; i++) calculateLinear__VarAD(y+i);

    printf("Meow6\n");

    printf("%le %le\n", y[0].data, y[1].data);

    printf("Meow7\n");

    for(int i=0; i<2; i++) delete__VarAD(y+i);
    for(int i=0; i<2; i++) delete__VarAD(x+i);
}