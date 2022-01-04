#ifndef Channel_h
#define Channel_h
#pragma pack(1)

#include <math.h>

//INCLUDES_BEGIN
#include "../../../pyad/VarAD/VarAD.h"
#include "../../../pyad/JacAD/JacAD.h"
#include "../ADF/ADF_deriv1/ADF_deriv1.h"
#include "../ADF/ADF_deriv2/ADF_deriv2.h"
#include "../ADF/ADF_dirichiletBC/ADF_dirichiletBC.h"
#include "../ADF/ADF_neumannBC/ADF_neumannBC.h"
#include "../ADF/ADF_residuals/ADF_residuals.h"
//INCLUDES_END

typedef struct
{
    int nPoints;
    int nStates;
    double nu;
    double dpdx;
    double *wallBC;
    double *y;
    double *U_values;
    double *R_values;
    VarAD *U;
    VarAD *U_y;
    VarAD *U_yy;
    VarAD *R;
    JacAD J;
}
Channel;

#endif