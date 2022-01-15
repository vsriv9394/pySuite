#include "../JacMatAD.h"
#include <string.h>

static int *_buffer;
static int _bufSize;

static void registerDeps(JacMatAD *self, FieldAD *X, int ind, int eInd);
static void endSort(int *arr, int n);
static int find(int entry, int *arr, int n);

void create__JacMatAD
(
    void *_self,
    FieldAD *inputs,
    FieldAD *outputs
)
{
    JacMatAD *self = _self;
    self->inputs = inputs; int M = inputs->size; int m = inputs->eSize;
    self->outputs = outputs; int N = outputs->size; int n = outputs->eSize;
    self->nRows = N*n; self->nCols = M*m; _buffer = calloc(M*m, sizeof(int));

    self->offsets = calloc(N*n+1, sizeof(int));
    for(int J=0; J<N; J++) for(int j=0; j<n; j++)
    {
        int iRow = J*n+j; _bufSize = 0; registerDeps(self, outputs, J, j);
        self->offsets[iRow+1] = self->offsets[iRow] + _bufSize;
    }

    self->colIds = calloc(self->offsets[N*n], sizeof(int));
    for(int J=0; J<N; J++) for(int j=0; j<n; j++)
    {
        int iRow = J*n+j; _bufSize = 0; registerDeps(self, outputs, J, j);
        memcpy(self->colIds+self->offsets[iRow], _buffer, _bufSize);
    }

    self->elems = calloc(self->offsets[N*n], sizeof(double));

    free(_buffer);
}

static void endSort(int *arr, int n)
{
    int temp = arr[n-1]; for(int i=n-1; i>0; i--)
    {
        if(arr[i-1]<temp) { arr[i] = temp; break; }
        else arr[i] = arr[i-1];
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

static void registerDeps(JacMatAD *self, FieldAD *X, int ind, int eInd)
{
    DepListAD *dep = &(X->depList);
    if(X==self->inputs)
    {
        int colId = ind*X->eSize+eInd;
        if(find(colId, _buffer, _bufSize)==-1)
        { _buffer[_bufSize++] = colId; endSort(_buffer, _bufSize); }
    }
    else while(dep->next!=NULL)
    {
        dep = dep->next;
        FieldAD *depField = dep->ptr;
        for(int eDep=0; eDep<depField->eSize; eDep++)
            registerDeps(self, depField, dep->conn[ind], eDep);
    }
}