#include <stdio.h>
#include "../JacobianAD.h"

int main()
{
    ArrayAD    x;
    ArrayAD    y;
    ArrayAD    z;
    JacobianAD J;

    init__ArrayAD(&x);
    init__ArrayAD(&y);
    init__ArrayAD(&z);
    init__JacobianAD(&J);

    x.shape[0] = 2;
    y.shape[0] = 2;
    z.shape[0] = 2;

    create__ArrayAD(&x);
    create__ArrayAD(&y);
    create__ArrayAD(&z);

    printf("x.eSize = %d\n", x.eSize);
    printf("y.eSize = %d\n", y.eSize);
    printf("z.eSize = %d\n", z.eSize);
    printf("\n");

    setNumDeps__ArrayAD(&y, 1);
    setDep__ArrayAD(&y, 0, &x, NULL, NULL, 0);
    //setDep__ArrayAD(&y, 1, &x, NULL, NULL, 0);
    setNumDeps__ArrayAD(&z, 1);
    setDep__ArrayAD(&z, 0, &y, NULL, NULL, 0);
    //setDep__ArrayAD(&z, 1, &y, NULL, NULL, 0);

    y.deps[0].indices[0] = 0;
    y.deps[0].indices[1] = 1;

    z.deps[0].indices[0] = 0;
    z.deps[0].indices[1] = 1;

    create__JacobianAD(&J, &z, &x);
    
    printf("J.M = %d\n", J.M);
    printf("J.m = %d\n", J.m);
    printf("J.N = %d\n", J.N);
    printf("J.n = %d\n", J.n);
    
    for(int i=0; i<J.M+1; i++)
        printf("%d ", J.offsets[i]);
    printf("\n");
    
    for(int i=0; i<J.M; i++)
    {
        for(int j=J.offsets[i]; j<J.offsets[i+1]; j++)
            printf("%d ", J.iBlocks[j]);
        printf("\n");
    }

    y.deps[0].entries[0] = 1.0; // (0,0) x (0,0)
    y.deps[0].entries[1] = 2.0; // (0,0) x (0,1)

    z.deps[0].entries[0] = 5.0; // (0,0) x (0,0)
    z.deps[0].entries[1] = 6.0; // (0,0) x (0,1)

    calculate__JacobianAD(&J);

    for(int  i=0;  i<J.M;  i++) for(int j=J.offsets[i]; j<J.offsets[i+1]; j++)
    for(int ii=0; ii<J.m; ii++) for(int jj=0; jj<J.n; jj++)
            printf("\t(%d,%d) (%d,%d) %+le\n", i, ii, J.iBlocks[j], jj, J.entries[(j*J.m+ii)*J.n+jj]);

    delete__ArrayAD(&x);
    delete__ArrayAD(&y);
    delete__ArrayAD(&z);

    delete__JacobianAD(&J);
}
