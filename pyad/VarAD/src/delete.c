#include "../VarAD.h"

void delete__VarAD
(
    void *_self
)
{
    VarAD *self = _self;
    
    if(self->depPtrs!=NULL) free(self->depPtrs);
    if(self->depSens!=NULL) free(self->depSens);
    
    init__VarAD(_self);
}