#include "../FVComm.h"

void eSet__FVComm
(
    void *_self,
    int index,
    int elemSize,
    void *elem
)
{
    FVComm *self = _self;
    memcpy(self->eBuffer+index*elemSize, elem, elemSize);
}