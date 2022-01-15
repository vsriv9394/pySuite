#include "../FieldAD.h"

void create__DepListAD
(
    void *_self,
    void *ptr,
    int *conn,
    double *sens
)
{
    FieldAD *self = _self;
    FieldAD *other = ptr;
    DepListAD *dep = &(self->depList);
    while(dep->next!=NULL) dep = dep->next;
    dep->next = calloc(1, sizeof(DepListAD));
    dep = dep->next; init__DepListAD(dep);
    create__DepListAD(dep, ptr, conn, sens);
    int M =  self->size; int m =  self->eSize;
    int N = other->size; int n = other->eSize;
    if(conn==NULL) dep->conn = calloc(M, sizeof(int));
    if(sens==NULL) dep->sens = calloc(M*m*n, sizeof(double));
}