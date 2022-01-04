#include "../Channel1D.h"

void delete__Channel1D
(
    void *_self
)
{
    Channel1D *self = _self;
    delete__Mesh1D(&(self->mesh));
    if(self->U!=NULL)
        free(self->U);
    self->U = NULL;
    if(self->R!=NULL)
        free(self->R);
    self->R = NULL;
}
