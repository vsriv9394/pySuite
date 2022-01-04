#ifndef FVData_h
#define FVData_h
#pragma pack(1)

#include "mpi.h"
#include <stdio.h>
#include <math.h>

//INCLUDES_BEGIN
#include "../../../pyad/VarAD/VarAD.h"
#include "../../../pyad/JacAD/JacAD.h"
#include "./FVComm/FVComm.h"
//INCLUDES_END

typedef struct
{
    int nDim;
    int nScal;
    int nFtr;
    int nno;
    int nno_g;
    int nno_gg;
    int ncv;
    int ncv_g;
    int ncv_gg;
    int ncv_ggf;
    int ncv_ggff;
    int nfa;
    int nfa_g;
    int nfa_gg;
    int nfa_ggf;
    int nfa_ggff;
    int (*cvofa)[2];
    int *markerOffsets_f;
    int *markerOffsets_ff;
    char **markerNames;
    double *x_no;
    double *x_fa;
    double *x_cv;
    double *n_fa;
    double *v_cv;
    VarAD states_AD;
    VarAD gradients_AD;
    VarAD fluxes_AD;
    VarAD sources_AD;
    VarAD residuals_AD;
    VarAD beta_AD;
    VarAD fluxes_AD;
    JacAD J;
    FVComm comm;
}
FVData;

void init__FVData(void *_self);
void create__Channel(void *_self, int nPoints, double *dy);
void delete__Channel(void *_self);
void setup__Channel(void *_self);
void calculateResiduals__Channel(void *_self);

#endif