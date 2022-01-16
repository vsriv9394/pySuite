#ifndef JacobianAD_h
#define JacobianAD_h
#pragma pack(1)

//INCLUDES_BEGIN
#include "../ArrayAD/ArrayAD.h"
//INCLUDES_END

typedef struct
{
    int            M;
    int            N;
    int            m;
    int            n;
    int     *offsets;
    int     *iBlocks;
    double  *entries;
    ArrayAD  *inputs;
    ArrayAD *outputs;
}
JacobianAD;

void init__JacobianAD(void *_self);
void delete__JacobianAD(void *_self);
void create__JacobianAD(void *_self, ArrayAD *outputs, ArrayAD *inputs);
void calculate__JacobianAD(void *_self);

#endif
