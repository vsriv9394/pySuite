#include "../JacobianAD.h"

void delete__JacobianAD
(
    void *_self
)
{
    JacobianAD *self = _self;
    if(self->offsets!=NULL) free(self->offsets);
    if(self->iBlocks!=NULL) free(self->iBlocks);
    if(self->entries!=NULL) free(self->entries);
    init__JacobianAD(_self);
}
