#include "../Channel1D.h"

void create__Channel1D
(
    void *_self,
    int nNodes,
    double dx0,
    double xMin,
    double xMax
)
{
    Channel1D *self = _self;
    create__Mesh1D(&(self->mesh), nNodes, dx0, xMin, xMax);
    if(self->U!=NULL) free(self->U);
    self->U = calloc(nNodes, sizeof(double)*2);
    if(self->R!=NULL) free(self->R);
    self->R = calloc(nNodes, sizeof(double)*2);
}
