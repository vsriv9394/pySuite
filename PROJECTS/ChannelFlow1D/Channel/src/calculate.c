#include "../Channel.h"

static ADF_dirichiletBC adf_dirichiletBC;
static ADF_neumannBC    adf_neumannBC;
static ADF_residuals    adf_residuals;

void calculate__Channel
(
    void *_self
)
{
    Channel *self = _self;
    int nP = self->nPoints; int nS = self->nStates;

    //=======================================================
    // Set input values to AD variables
    //=======================================================

    for(int i=0; i<nP; i++) for(int j=0; j<nS; j++)
        self->U[i*nS+j].data = self->U_values[i*nS+j];

    //=======================================================
    // Calculate gradients and hessians
    //=======================================================

    for(int i=1; i<nP-1; i++) for(int j=0; j<nS; j++)
        calculateLinear__VarAD(self->U_y + i*nS + j);

    for(int i=1; i<nP-1; i++) for(int j=0; j<nS; j++)
        calculateLinear__VarAD(self->U_yy + i*nS + j);

    //=======================================================
    // Calculate wall boundary residuals
    //=======================================================

    for(int j=0; j<nS; j++)
    {
        setVars__ADF_dirichiletBC(
            &adf_dirichiletBC,
            self->U + j,
            self->wallBC + j,
            self->R + j
        );
        
        calculate__ADF_dirichiletBC(
            &adf_dirichiletBC
        );
    }

    //=======================================================
    // Calculate centerline boundary residuals
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
        
        calculate__ADF_neumannBC(
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

        calculate__ADF_residuals(
            &adf_residuals
        );
    }

    //=======================================================
    // Get residual values from AD variables
    //=======================================================

    for(int i=0; i<nP; i++) for(int j=0; j<nS; j++)
        self->R_values[i*nS+j] = self->R[i*nS+j].data;

    //=======================================================
    // Calculate Jacobian values
    //=======================================================

    calculate__JacAD(&self->J);
    calculate__JacAD(&self->J_cb1);
}
