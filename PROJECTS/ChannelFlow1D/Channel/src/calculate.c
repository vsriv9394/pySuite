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
    int nP = self->nPoints; int nS = self->nStates; double zero = 0.0;

    for(int j=0; j<self->nStates; j++)
    {
        for(int i=1; i<nP-1; i++) self->U[i*nS+j].data = self->U_values[i*nS+j];

        setVars__ADF_dirichiletBC(&adf_dirichiletBC,
        &(self->wallBC[j]), &(self->U[j]));
        calculate__ADF_dirichiletBC(&adf_dirichiletBC);
        self->U_values[j] = self->U[j].data;

        setVars__ADF_neumannBC(&adf_neumannBC, &(self->U[(nP-2)*nS+j]),
        &(self->U[(nP-3)*nS+j]), &(self->y[nP-1]), &(self->y[nP-2]),
        &(self->y[nP-3]), &zero, &(self->U[(nP-1)*nS+j]));
        calculate__ADF_neumannBC(&adf_neumannBC);
        self->U_values[(nP-1)*nS+j] = self->U[(nP-1)*nS+j].data;

        for(int i=1; i<nP-1; i++)
        {
            calculateLinear__VarAD(&(self->U_y[i*nS+j]));
            calculateLinear__VarAD(&(self->U_yy[i*nS+j]));
        }
    }

    for(int i=1; i<self->nPoints-1; i++)
    {
        setVars__ADF_residuals(&adf_residuals, &(self->U[i*nS]),
        &(self->U_y[i*nS]), &(self->U_yy[i*nS]), &(self->nu),
        &(self->dpdx), &(self->y[i]), &(self->R[i*nS]));
        calculate__ADF_residuals(&adf_residuals);
        for(int j=0; j<self->nStates; j++)
            self->R_values[(i-1)*nS+j] = self->R[i*nS+j].data;
    }

    calculate__JacAD(&self->J);
}