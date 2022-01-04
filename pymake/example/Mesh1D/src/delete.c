#include "../Mesh1D.h"

void delete__Mesh1D
(
    void *_self
)
{
    Mesh1D *self = _self;
    self->nNodes = 0;
    if(self->x!=NULL)
        free(self->x);
    self->x = NULL;
}
