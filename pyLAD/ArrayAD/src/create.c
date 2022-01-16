#include "../ArrayAD.h"

void create__ArrayAD
(
    void *_self
)
{
    ArrayAD *self = _self;

    self->eSize = 1;
    for(int i=1; i<4; i++)
        self->eSize *= self->shape[i];
    
    self->data = calloc(self->shape[0]*self->eSize, sizeof(double));
}
