#ifndef FVData_h
#define FVData_h
#pragma pack(1)

#include <stdio.h>
#include <math.h>

//INCLUDES_BEGIN
#include "../FVCellContainer/FVCellContainer.h"
#include "../FVFaceContainer/FVFaceContainer.h"
#include "../FVMarkerContainer/FVMarkerContainer.h"
#include "../../../pyad/VarAD/VarAD.h"
#include "../../../pyad/JacAD/JacAD.h"
//INCLUDES_END

typedef struct
{
    FVCellContainer *cells;
    FVFaceContainer *faces;
    FVMarkerContainer *markers;
    JacAD dRdU;
    JacAD dRdbeta;
}
FVData;

void init__FVData(void *_self);
void delete__FVData(void *_self);
void create__FVData(void *_self, int nno, int ncv, int nfa, int nbc);
void setup__FVData(void *_self);
void calculate__FVData(void *_self);

#endif