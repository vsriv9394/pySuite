#include "../FVData.h"

void delete__FVData
(
    void *_self
)
{
    FVData *self = _self;
    if(self->faobc_i != NULL) free(self->faobc_i);
    if(self->cvobc_i != NULL) free(self->cvobc_i);
    if(self->cvofa   != NULL) free(self->cvofa  );
    if(self->x_no    != NULL) free(self->x_no   );
    if(self->x_fa    != NULL) free(self->x_fa   );
    if(self->x_cv    != NULL) free(self->x_cv   );
    if(self->n_fa    != NULL) free(self->n_fa   );
    if(self->v_cv    != NULL) free(self->v_cv   );
    if(self->U       != NULL) free(self->U      );
    if(self->Up      != NULL) free(self->Up     );
    if(self->grad_Up != NULL) free(self->grad_Up);
    if(self->F       != NULL) free(self->F      );
    if(self->R       != NULL) free(self->R      );
    delete__JacAD(&(self->dRdU));
}