#include<stdio.h>

int bin( int low, int high, int arr[], int x)
{
    int mid = (low+high)/2;

    if(low > high)                               //not found
    return -1;

    else if(x > arr[mid])
    return(bin(mid+1, high, arr, x));

    else if(x < arr[mid])
    return(bin(low, mid-1, arr, x));

    else if(low != mid)
    return(bin(low, mid, arr, x));

    else
    return(mid);

    
}

int main()
{
    int n;                               //number of elements in array
    scanf("%d", &n);

    long int queries;
    scanf("%ld", &queries);

    int arr[n];
    for(int i=0;i<n;i++)                   //taking array input
    {
        scanf("%d",&arr[i]);
    }

    int x;                              //element to search for

    for(long int i = 0; i < queries; i++)
    {
        scanf("%d",&x);

        printf("%d\n", bin(0, n, arr, x));
    }

    return 0;
}
