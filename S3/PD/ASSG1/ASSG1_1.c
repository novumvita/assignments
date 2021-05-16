#include<stdio.h>

int main()
{
    int n;                               //number of elements in array
    scanf("%d", &n);

    int arr[n];
    for(int i=0;i<n;i++)                   //taking array input
    {
        scanf("%d",&arr[i]);
    }

    int x;                              //element to search for
    scanf("%d",&x);

    int flag=1;

    for(int i=0;i<n;i++)                    //searching
    {
        if(arr[i]==x)
        {
            flag=0;
            printf("%d ",i);
        }
    }

    if(flag)                        //if no element matches the search
    printf("-1");
    
    return 0;
}