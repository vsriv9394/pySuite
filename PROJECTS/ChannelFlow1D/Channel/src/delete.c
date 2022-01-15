#include "../Channel.h"

void delete__Channel
(
    void *_self
)
{
    Channel *self = _self;
    
    if(self->wallBC!=NULL) free(self->wallBC);
    
    if(self->y       !=NULL) free(self->y);
    if(self->U_values!=NULL) free(self->U_values);
    if(self->R_values!=NULL) free(self->R_values);
    
    if(self->U   !=NULL) free(self->U);
    if(self->U_y !=NULL) free(self->U_y);
    if(self->U_yy!=NULL) free(self->U_yy);
    if(self->R   !=NULL) free(self->R);
    
    delete__VarAD(&(self->cb1));
    delete__JacAD(&(self->J));
    delete__JacAD(&(self->J_cb1));
}
