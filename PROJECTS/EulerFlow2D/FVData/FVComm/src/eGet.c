#include "../FVComm.h"

void eGet__FVComm
(
    void *_self,
    int index,
    int elemSize,
    void *elem
)
{
    FVComm *self = _self;
    memcpy(elem, self->eBuffer+index*elemSize, elemSize);
}