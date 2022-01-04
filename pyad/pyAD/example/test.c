#include "adFunc__cons2prim/adFunc__cons2prim.h"

int main()
{
    VarAD Uc[4], Up[4]; double R=1.0, gamma=1.4;
    for(int i=0; i<4; i++)
    {
        init__VarAD(Uc+i);
        init__VarAD(Up+i);
    }
    adFunc__cons2prim cons2prim;
    init__adFunc__cons2prim(&cons2prim);
    setVars__adFunc__cons2prim(&cons2prim, Uc, &R, &gamma, Up);
    setup__adFunc__cons2prim(&cons2prim);

    JacAD jac;
    init__JacAD(&jac);
    create__JacAD(&jac, 4, 4, Uc, Up);

    Uc[0].value = 0.5;
    Uc[1].value = 0.1;
    Uc[2].value = 0.2;
    Uc[3].value = 1.0 / (1.4 - 1.0) + 0.05;
    
    calculate__adFunc__cons2prim(&cons2prim);
    for(int i=0; i<4; i++) printf("%le\n", Up[i].value);
    
    calculate__JacAD(&jac);
    for(int i=0; i<jac.nOutputs; i++)
        for(int j=jac.offsets[i]; j<jac.offsets[i+1]; j++)
            printf("%d %d %le\n", i, jac.colIds[j], jac.elems[j]);

    delete__JacAD(&jac);
    for(int i=0; i<4; i++)
    {
        delete__VarAD(Up+i);
        delete__VarAD(Uc+i);
    }
}