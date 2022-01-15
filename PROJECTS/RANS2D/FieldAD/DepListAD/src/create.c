#include "../DepListAD.h"

void create__DepListAD
(
    void *_self,
    void *ptr,
    int *conn,
    double *sens
)
{
    DepListAD *self = _self;
    self->ptr = ptr;
    if (conn==NULL) self->connIsACopy = 0;
    else self->conn = conn;
    if (sens==NULL) self->sensIsACopy = 0;
    else self->sens = sens;
}