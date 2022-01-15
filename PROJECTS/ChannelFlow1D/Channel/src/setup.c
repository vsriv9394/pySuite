#include <stdio.h>
#include "../Channel.h"

static ADF_deriv1       adf_deriv1;
static ADF_deriv2       adf_deriv2;
static ADF_dirichiletBC adf_dirichiletBC;
static ADF_neumannBC    adf_neumannBC;
static ADF_residuals    adf_residuals;

static void allocVars(Channel *self);
static void createMesh(Channel *self, double dy_0);
static double getGrowthFactor(int nPoints, double dy_0);

void setup__Channel
(
    void *_self,
    double dy_0
)
{
    Channel *self = _self;
    int nP = self->nPoints; int nS = self->nStates;

    allocVars(self);
    createMesh(self, dy_0);

    //=======================================================
    // Setup gradients
    //=======================================================

    for(int i=1; i<nP-1; i++) for(int j=0; j<nS; j++)
    {
        setVars__ADF_deriv1(
            &adf_deriv1,
            self->U + (i-1)*nS + j,
            self->U + (i+0)*nS + j,
            self->U + (i+1)*nS + j,
            self->y + i-1,
            self->y + i+0,
            self->y + i+1,
            self->U_y + i*nS + j
        );
        
        setup__ADF_deriv1(
            &adf_deriv1
        );
        
        calculate__ADF_deriv1(
            &adf_deriv1
        );
    }

    //=======================================================
    // Setup hessians
    //=======================================================

    for(int i=1; i<nP-1; i++) for(int j=0; j<nS; j++)
    {
        setVars__ADF_deriv2(
            &adf_deriv2,
            self->U + (i-1)*nS + j,
            self->U + (i+0)*nS + j,
            self->U + (i+1)*nS + j,
            self->y + i-1,
            self->y + i+0,
            self->y + i+1,
            self->U_yy + i*nS + j
        );
        
        setup__ADF_deriv2(
            &adf_deriv2
        );
        
        calculate__ADF_deriv2(
            &adf_deriv2
        );
    }

    //=======================================================
    // Setup wall boundary residuals
    //=======================================================

    for(int j=0; j<nS; j++)
    {
        setVars__ADF_dirichiletBC(
            &adf_dirichiletBC,
            self->U + j,
            self->wallBC + j,
            self->R + j
        );
        
        setup__ADF_dirichiletBC(
            &adf_dirichiletBC
        );
    }

    //=======================================================
    // Setup centerline boundary residuals
    //=======================================================

    for(int j=0; j<nS; j++)
    {
        double zero = 0.0;

        setVars__ADF_neumannBC(
            &adf_neumannBC,
            self->U + (nP-1)*nS + j,
            self->U + (nP-2)*nS + j,
            self->U + (nP-3)*nS + j,
            self->y + (nP-1)       ,
            self->y + (nP-2)       ,
            self->y + (nP-3)       ,
            &zero                  ,
            self->R + (nP-1)*nS + j
        );
        
        setup__ADF_neumannBC(
            &adf_neumannBC
        );
    }

    //=======================================================
    // Calculate internal residuals
    //=======================================================

    for(int i=1; i<nP-1; i++)
    {
        setVars__ADF_residuals(
            &adf_residuals,
            self->U    + i*nS,
            self->U_y  + i*nS,
            self->U_yy + i*nS,
            &(self->cb1)     ,
            &(self->nu)      ,
            &(self->dpdx)    ,
            self->y + i      ,
            self->R + i*nS
        );

        setup__ADF_residuals(
            &adf_residuals
        );
    }

    //=======================================================
    // Create Jacobians
    //=======================================================

    create__JacAD(
        &self->J,
        nP*nS,
        nP*nS,
        self->U,
        self->R
    );
    
    create__JacAD(
        &self->J_cb1,
        1,
        nP*nS, 
        &(self->cb1),
        self->R
    );
}

static void allocVars(Channel *self)
{
    int nP = self->nPoints; int nS = self->nStates;

    self->wallBC   = calloc(nS,    sizeof(double));

    self->y        = calloc(nP,    sizeof(double));
    self->U_values = calloc(nP*nS, sizeof(double));
    self->R_values = calloc(nP*nS, sizeof(double));
    
    self->U        = calloc(nP*nS, sizeof(VarAD));
    self->U_y      = calloc(nP*nS, sizeof(VarAD));
    self->U_yy     = calloc(nP*nS, sizeof(VarAD));
    self->R        = calloc(nP*nS, sizeof(VarAD));
}

static void createMesh(Channel *self, double dy_0)
{
    int nP = self->nPoints; int nS = self->nStates;
    
    double gf = getGrowthFactor(nP, dy_0);
    
    self->y[0] = 0.0;
    
    for(int i=1; i<nP-1; i++)
    {
        self->y[i] = dy_0*(1-pow(gf, i))/(1-gf);
    }
    
    self->y[nP-1] = 1.0;
}

static double getGrowthFactor(int nPoints, double dy_0)
{
    double gf = 2.0; double d_gf = -0.1;
    double val = dy_0*(1-pow(gf, nPoints-1))/(1-gf) - 1.0;
    if(val<0.0) d_gf *= -1;
    while(val*val>0.0 && d_gf*d_gf>1e-20)
    {
        double prevVal = val; gf += d_gf;
        if(gf==1.0) { gf -= d_gf; d_gf *= 0.1; continue; }
        val = dy_0*(1-pow(gf, nPoints-1))/(1-gf) - 1.0;
        if(prevVal*val<0.0) d_gf *= -0.1;
    }
    printf("Mesh growth factor = %le\n", gf);
    return gf;
}
