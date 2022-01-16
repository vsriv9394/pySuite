//=================================================================
// Sort an array which is already sorted save the last element
//=================================================================
static void endSort(int *arr, int n)
{
    int newElement = arr[n-1];

    for(int i=n-2; i>=0; i--)
    {
        if(arr[i] < newElement)
        {
            arr[i+1] = newElement;
            return;
        }
        else
        {
            arr[i+1] = arr[i];
        }
    }

    arr[0] = newElement;
}

//=================================================================
// Binary search for a given entry
//=================================================================
static int find(int entry, int *arr, int n)
{
    if(n==0) return -1; int off = 0, nb2;
    
    while(n>1)
    {
        nb2 = n>>1;
        if(arr[off+nb2]>entry) { n = nb2; }
        else { off += nb2; n -= nb2; }
    }
    
    if(arr[off]==entry) return off; else return -1;
}
