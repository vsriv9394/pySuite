#include <stdio.h>
#include "../ArrayAD.h"

int main()
{
    ArrayAD x;
    ArrayAD y;

    init__ArrayAD(&x);
    init__ArrayAD(&y);

    x.shape[0] = 1;
    x.shape[1] = 2;
    y.shape[0] = 2;

    create__ArrayAD(&x);
    create__ArrayAD(&y);

    setNumDeps__ArrayAD(&y, 1);
    setDep__ArrayAD(&y, 0, &x, NULL, NULL, 0);

    printf("Here 1\n");

    y.deps[0].indices[0] = 0;
    y.deps[0].indices[1] = 0;

    y.deps[0].entries[0] = 1.0;
    y.deps[0].entries[1] = 2.0;
    y.deps[0].entries[2] = 3.0;
    y.deps[0].entries[3] = 4.0;

    printf("Here 2\n");

    x.data[0] = 5.0;
    x.data[1] = 6.0;

    calculateLinear__ArrayAD(&y);

    printf("%le %le\n", y.data[0], y.data[1]);

    delete__ArrayAD(&x);
    delete__ArrayAD(&y);
}
