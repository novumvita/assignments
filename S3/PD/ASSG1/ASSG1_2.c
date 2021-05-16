#include<stdio.h>

void swap(int*x, int*y)
{
    *x=*x+*y;
    *y=*x-*y;
    *x=*x-*y;
    return;
}

int main()
{
    int n;                               //number of elements in array
    scanf("%d", &n);

    int arr[n];
    for(int i=0;i<n;i++)                   //taking array input
    {
        scanf("%d",&arr[i]);
    }

    for(int i=1;i<n;i++)               //sorting
    {
        for(int j=0;j<n-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }

    for(int i=0;i<n;i++)                    //printing
    {
        printf("%d ",arr[i]);
    }
    return 0;
}