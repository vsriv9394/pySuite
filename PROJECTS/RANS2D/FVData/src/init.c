#include "../FVData.h"

void init__FVData
(
    void *_self
)
{
    FVData *self = _self;
    self->nno = 0;
    self->ncv = 0;
    self->nfa = 0;
    self->nbc = 0;
    self->faobc_i = NULL;
    self->cvobc_i = NULL;
    self->cvofa = NULL;
    self->x_no = NULL;
    self->x_fa = NULL;
    self->x_cv = NULL;
    self->n_fa = NULL;
    self->v_cv = NULL;
    self->U = NULL;
    self->Up = NULL;
    self->grad_Up = NULL;
    self->F = NULL;
    self->R = NULL;
    init__JacAD(&(self->dRdU));
}