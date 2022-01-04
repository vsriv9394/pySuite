#include "../FVComm.h"

void iSet__FVComm
(
    void *_self,
    int index,
    int elemSize,
    void *elem
)
{
    FVComm *self = _self;
    memcpy(self->iBuffer+index*elemSize, elem, elemSize);
}