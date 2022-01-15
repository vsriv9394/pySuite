#include "../JacMatAD.h"
#include <string.h>

static int find(int entry, int *arr, int n);
static void calc(JacMatAD *self, FieldAD *X, int ind, int eInd, int iRow, double sens);

void calculate__JacMatAD
(
    void *_self
)
{
    JacMatAD *self = _self;
    int M = self->inputs->size; int m = self->inputs->eSize;
    int N = self->outputs->size; int n = self->outputs->eSize;
    for(int i=0; i<self->offsets[N*n]; i++) self->elems[i] = 0.0;
    for(int J=0; J<N; J++) for(int j=0; j<n; j++) calc(self, self->outputs, J, j, J*n+j, 1.0);
}

static void calc(JacMatAD *self, FieldAD *X, int ind, int eInd, int iRow, double sens)
{
    DepListAD *dep = &(X->depList);
    if(X==self->inputs)
    {
        int N = self->outputs->eSize;
        int colId = ind*X->eSize+eInd;
        int inz = self->colIds + self->offsets[iRow] + 
            find(colId, self->colIds + self->offsets[iRow],
                 self->offsets[iRow+1] - self->offsets[iRow]);
        self->elems[inz] += sens;
    }
    else while(dep->next!=NULL)
    {
        dep = dep->next;
        FieldAD *depField = dep->ptr;
        for(int eDep=0; eDep<depField->eSize; eDep++)
        {
            calc(self, depField, dep->conn[ind], eDep, iRow, sens);
        }
    }
}

static int find(int entry, int *arr, int n)
{
    if (n<1) return -1; int nb2, nb2p1; int *arr_orig = arr;
    while(n>1)
    {
        nb2 = n>>1;
        if(arr[nb2]==entry) { arr+=nb2; break; }
        else if(arr[nb2]>entry) n=nb2;
        else { nb2p1=nb2+1; n-=nb2p1; arr+=nb2p1;  }
    }
    if(arr[0]==entry) return (int)(arr-arr_orig);
    else return -1;
}