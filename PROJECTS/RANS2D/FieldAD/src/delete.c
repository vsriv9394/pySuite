#include "../FieldAD.h"

void delete__FieldAD
(
    void *_self
)
{
    FieldAD *self = _self;
    if(self->data!=NULL) free(self->data);
    delete__DepListAD(&(self->depList));
}