#include "../DepListAD.h"

void delete__DepListAD
(
    void *_self
)
{
    DepListAD *self = _self;
    if(self->next!=NULL) { delete__DepListAD(self->next); free(self->next); }
    if(self->ptr!=NULL) { free(self->ptr); }
    if(self->connIsACopy==0) { free(self->conn); }
    if(self->sensIsACopy==0) { free(self->sens); }
}