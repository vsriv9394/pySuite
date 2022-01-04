#include "../Mesh1D.h"

static double growthFactor(int nNodes, double dx0, double Dx);

void create__Mesh1D
(
    void *_self,
    int nNodes,
    double dx0,
    double xMin,
    double xMax
)
{
    Mesh1D *self = _self;
    double gf = growthFactor(nNodes, dx0, xMax-xMin);
    self->nNodes = nNodes;
    if(self->x!=NULL) free(self->x);
    self->x = (double*)calloc(nNodes, sizeof(double));
    double dx = dx0;
    self->x[0] = xMin;
    for(int i=1; i<nNodes-1; i++)
    {
        self->x[i] = self->x[i-1] + dx;
        dx *= gf;
    }
    self->x[nNodes-1] = xMax;
}

static double growthFactor(int nNodes, double dx0, double Dx)
{
    double tol = 1e-8;
    double gf = 1.1 + tol;
    double dgf = 0.01;
    double Dxc = dx0 * (pow(gf, nNodes-2) - 1) / (gf - 1);
    while(dgf>tol)
    {
        gf += dgf * (Dx>Dxc ? 1 : -1);
        //printf("%le %le\n", gf, Dxc);
        double Dxc_temp = dx0 * (pow(gf, nNodes-1) - 1) / (gf - 1);
        if((Dxc_temp-Dx)*(Dxc-Dx)<0.0) dgf *= 0.1;
        Dxc = Dxc_temp;
    }
    return gf;
}
