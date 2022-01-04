#include "../FVComm.h"

void iGet__FVComm
(
    void *_self,
    int index,
    int elemSize,
    void *elem
)
{
    FVComm *self = _self;
    memcpy(elem, self->iBuffer+index*elemSize, elemSize);
}