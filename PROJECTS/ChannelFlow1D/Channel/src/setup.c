#include <stdio.h>
#include "../Channel.h"

static ADF_deriv1       adf_deriv1;
static ADF_deriv2       adf_deriv2;
static ADF_dirichiletBC adf_dirichiletBC;
static ADF_neumannBC    adf_neumannBC;
static ADF_residuals    adf_residuals;

static double getGrowthFactor(int nPoints, double dy_0);

void setup__Channel
(
    void *_self,
    double dy_0
)
{
    Channel *self = _self;
    int nP = self->nPoints; int nS = self->nStates; double zero = 0.0;

    self->wallBC   = calloc(nP, sizeof(double));
    self->y        = calloc(nP, sizeof(double));
    self->U        = calloc(nP*nS, sizeof(VarAD));
    self->U_y      = calloc(nP*nS, sizeof(VarAD));
    self->U_yy     = calloc(nP*nS, sizeof(VarAD));
    self->R        = calloc(nP*nS, sizeof(VarAD));
    self->U_values = calloc(nP*nS, sizeof(double));
    self->R_values = calloc((nP-2)*nS, sizeof(double));
    
    double gf = getGrowthFactor(nP, dy_0); printf("gf = %le\n", gf);
    self->y[0] = 0.0;
    for(int i=1; i<nP; i++)
    {
        self->y[i] = dy_0*(1-pow(gf, i))/(1-gf);
    }
    self->y[nP-1] = 1.0;

    for(int j=0; j<self->nStates; j++)
    {
        setVars__ADF_dirichiletBC(&adf_dirichiletBC,
        &(self->wallBC[j]), &(self->U[j]));
        setup__ADF_dirichiletBC(&adf_dirichiletBC);

        setVars__ADF_neumannBC(&adf_neumannBC, &(self->U[(nP-2)*nS+j]),
        &(self->U[(nP-3)*nS+j]), &(self->y[nP-1]), &(self->y[nP-2]),
        &(self->y[nP-3]), &zero, &(self->U[(nP-1)*nS+j]));
        setup__ADF_neumannBC(&adf_neumannBC);

        for(int i=1; i<nP-1; i++)
        {
            setVars__ADF_deriv1(&adf_deriv1, &(self->U[(i-1)*nS+j]),
            &(self->U[i*nS+j]), &(self->U[(i+1)*nS+j]), &(self->y[i-1]),
            &(self->y[i]), &(self->y[i+1]), &(self->U_y[i*nS+j]));
            setup__ADF_deriv1(&adf_deriv1);
            calculate__ADF_deriv1(&adf_deriv1);
        }

        for(int i=1; i<nP-1; i++)
        {
            setVars__ADF_deriv2(&adf_deriv2, &(self->U[(i-1)*nS+j]),
            &(self->U[i*nS+j]), &(self->U[(i+1)*nS+j]), &(self->y[i-1]),
            &(self->y[i]), &(self->y[i+1]), &(self->U_yy[i*nS+j]));
            setup__ADF_deriv2(&adf_deriv2);
            calculate__ADF_deriv2(&adf_deriv2);
        }
    }

    for(int i=1; i<nP-1; i++)
    {
        setVars__ADF_residuals(&adf_residuals, &(self->U[i*nS]),
        &(self->U_y[i*nS]), &(self->U_yy[i*nS]), &self->nu,
        &self->dpdx, &(self->y[i]), &(self->R[i*nS]));
        setup__ADF_residuals(&adf_residuals);
    }

    create__JacAD(&self->J, (nP-2)*nS, (nP-2)*nS, (void*)(self->U + nS), (void*)(self->R + nS));
}

static double getGrowthFactor(int nPoints, double dy_0)
{
    double gf = 2.0; double d_gf = -0.1;
    double val = dy_0*(1-pow(gf, nPoints-1))/(1-gf) - 1.0;
    if(val<0.0) d_gf *= -1;
    while(val*val>0.0 && d_gf*d_gf>1e-20)
    {
        //printf("gf = %le\n", gf);
        double prevVal = val; gf += d_gf;
        if(gf==1.0) { gf -= d_gf; d_gf *= 0.1; continue; }
        val = dy_0*(1-pow(gf, nPoints-1))/(1-gf) - 1.0;
        if(prevVal*val<0.0) d_gf *= -0.1;
    }
    return gf;
}