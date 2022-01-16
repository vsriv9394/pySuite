#include "../utils.h"
#include <stdio.h>

int main()
{
    //{5, 23, 76, 102, 342, 651, 987};
    int A[7]; int size = 0;
    A[size++] = 342; endSort(A, size);
    A[size++] =  76; endSort(A, size);
    A[size++] =  23; endSort(A, size);
    A[size++] = 651; endSort(A, size);
    A[size++] = 987; endSort(A, size);
    A[size++] = 102; endSort(A, size);
    A[size++] =   5; endSort(A, size);
    for(int i=0; i<7; i++) printf("%d ", A[i]); printf("\n");

    printf("%d\n", find(5, A, 7));
    printf("%d\n", find(23, A, 7));
    printf("%d\n", find(76, A, 7));
    printf("%d\n", find(102, A, 7));
    printf("%d\n", find(342, A, 7));
    printf("%d\n", find(651, A, 7));
    printf("%d\n", find(987, A, 7));
    
    printf("%d\n", find(1+3, A, 7));
    printf("%d\n", find(1+5, A, 7));
    printf("%d\n", find(1+23, A, 7));
    printf("%d\n", find(1+76, A, 7));
    printf("%d\n", find(1+102, A, 7));
    printf("%d\n", find(1+342, A, 7));
    printf("%d\n", find(1+651, A, 7));
    printf("%d\n", find(1+987, A, 7));
}
