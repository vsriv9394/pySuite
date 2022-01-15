#include "../DepListAD.h"

void init__DepListAD
(
    void *_self
)
{
    DepListAD *self = _self;
    self->next = NULL;
    self->ptr  = NULL;
    self->conn = NULL;
    self->sens = NULL;
    self->connIsACopy = 1;
    self->sensIsACopy = 1;
}