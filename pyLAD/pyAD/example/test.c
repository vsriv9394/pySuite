#include "ADF_cons2prim/ADF_cons2prim.h"

#define DEPINDEX__Up__Uc 0

int main()
{
    double R = 1.0;
    double gamma = 1.4;

    //==================================================================
    // Create variables
    //==================================================================

    ADF_cons2prim cons2prim;
    init__ADF_cons2prim(&cons2prim);
    
    ArrayAD Uc;
    init__ArrayAD(&Uc);
    Uc.shape[0] = 1;
    Uc.shape[1] = 4;
    create__ArrayAD(&Uc);

    ArrayAD Up;
    init__ArrayAD(&Up);
    Up.shape[0] = 1;
    Up.shape[1] = 4;
    create__ArrayAD(&Up);
    setNumDeps__ArrayAD(&Up, 1);
    setDep__ArrayAD(&Up, DEPINDEX__Up__Uc, &Uc, NULL, NULL, 1);

    JacobianAD J;
    init__JacobianAD(&J);
    create__JacobianAD(&J, &Up, &Uc);

    //==================================================================
    // Set input values
    //==================================================================

    Uc.data[0] = 0.5;
    Uc.data[1] = 0.1;
    Uc.data[2] = 0.2;
    Uc.data[3] = 1.0 / (1.4 - 1.0) + 0.05;

    //==================================================================
    // Calculate outputs and sensitivities
    //==================================================================

    cons2prim.Uc         = Uc.data + 0;
    cons2prim.R          = &R;
    cons2prim.gamma      = &gamma;
    cons2prim.Up         = Up.data + 0;
    cons2prim.d_Up__d_Uc = Up.deps[DEPINDEX__Up__Uc].entries
                         + 0 * Up.eSize * Uc.eSize;

    calculate__ADF_cons2prim(&cons2prim);

    calculate__JacobianAD(&J);

    //==================================================================
    // Print outputs
    //==================================================================

    for(int i=0; i<4; i++)
    {
        printf("%le\n", Up.data[i]);
    }
    printf("All ok\n");

    int jacind=0; for(int i=0; i<J.M; i++)
    for(int j=J.offsets[i]; j<J.offsets[i+1]; j++)
    for(int ii=0; ii<J.m; ii++) for(int jj=0; jj<J.n; jj++)
    {
        printf("Row=(%d,%d) Column=(%d,%d) Entry=%+le\n",
               i, ii, j, jj, J.entries[jacind++]);
    }

    //==================================================================
    // Delete stuff
    //==================================================================

    delete__JacobianAD(&J);
    delete__ArrayAD(&Up);
    delete__ArrayAD(&Uc);
}
