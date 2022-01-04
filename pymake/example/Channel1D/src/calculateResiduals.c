#include "../Channel1D.h"

static double getEddyVisc(double nuSA, double nu);

static double getDestruction(double kappa, double y, double S, double nuSA);

void calculateResiduals__Channel1D
(
    void *_self,
    double (*U)[2],
    double (*R)[2]
)
{
    Channel1D *self = _self;

    static double dpdx      = -1.0;
    static double nu        =  1e-3;

    static double cb1       =  0.1355;
    static double cb2       =  0.622;
    static double inv_sigma =  1.5;
    static double kappa     =  0.41;

    // Internal nodes
    for(int i=1; i<self->mesh.nNodes-1; i++)
    {
        double ym, y, yp, um, u, up, nuTm, nuT, nuTp, nuSAm, nuSA, nuSAp;
        ym = self->mesh.x[i-1]; um = U[i-1][0];
        y  = self->mesh.x[i];   u  = U[i  ][0];
        yp = self->mesh.x[i+1]; up = U[i*1][0];
        nuSAm = U[i-1][1]; nuTm = getEddyVisc(nuSAm, nu);
        nuSA  = U[i  ][1]; nuT  = getEddyVisc(nuSA, nu);
        nuSAp = U[i+1][1]; nuTp = getEddyVisc(nuSAp, nu);

        double u_y     = 0.5 * ((up-u)/(yp-y) + (u-um)/(y-ym));
        double u_yy    = 2.0 * ((up-u)/(yp-y) - (u-um)/(y-ym)) / (yp-ym);

        double nuSA_y  = 0.5 * ((nuSAp-nuSA)/(yp-y) + (nuSA-nuSAm)/(y-ym));
        double nuSA_yy = 2.0 * ((nuSAp-nuSA)/(yp-y) - (nuSA-nuSAm)/(y-ym)) / (yp-ym);

        double nuT_y   = 0.5 * ((nuTp-nuT)/(yp-y) + (nuT-nuTm)/(y-ym));

        double S = fabs(u_y) + nuSA/(kappa*kappa*y*y) * (1.0 - nuSA/(nu + nuT));

        R[i][0] = -dpdx + (nu + nuT) * u_yy + nuT_y * u_y;
        R[i][1] = cb1 * S * nuSA
                + getDestruction(kappa, y, S, nuSA)
                + inv_sigma * ( (nu + nuSA) * nuSA_yy + (cb2 + 1.0) * nuSA_y * nuSA_y);
    }

    R[0][0] = -U[0][0];
    R[0][1] = -U[0][1];

    int n = self->mesh.nNodes; double *y = self->mesh.x;
    double g = (y[n-1] - y[n-2])/(y[n-1] - y[n-3]);
    
    R[n-1][0]  = U[n-1][0]*(1-g*g) - U[n-2][0] + U[n-3][0]*g*g;
    R[n-1][0] /= g * (y[n-3] - y[n-2]);

    R[n-1][1]  = U[n-1][1]*(1-g*g) - U[n-2][1] + U[n-3][1]*g*g;
    R[n-1][1] /= g * (y[n-3] - y[n-2]);
}

static double getEddyVisc(double nuSA, double nu)
{
    static double cubed_cv1 =  357.911;
    double chi = nuSA/nu;
    double cubed_chi = chi*chi*chi;
    double fv1 = cubed_chi / (cubed_chi + cubed_cv1);
    return nuSA * fv1;
}

static double getDestruction(double kappa, double y, double S, double nuSA)
{
    static double cw1          =  0.1355/0.41/0.41 + 1.622*1.5;
    static double cw2          =  0.3;
    static double cw3_raised_6 =  64.0;
    double kappa_times_y = kappa * y;
    double r  = fmin(nuSA / (S * kappa_times_y * kappa_times_y), 10.0);
    double g  = r + cw2 * (pow(r,6) - r);
    double fw = g * pow((1.0 + cw3_raised_6)/(pow(g,6) + cw3_raised_6), 1.0/6.0);
    return cw1 * fw * nuSA * nuSA / y / y;
}
