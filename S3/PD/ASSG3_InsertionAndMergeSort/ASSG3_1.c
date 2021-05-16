#include<stdio.h>

void print(int arr[], int n)
{
    for(int i=0;i<n;i++)                   //printing the array
    {
        printf("%d ",arr[i]);
    }
}

int insertionsort(int arr[], int n)
{
    int count = 0;

    int key;

    for(int i=1;i<n;i++)
    {
        key = arr[i];
        int j = i-1;

        while(j >= 0)
        {
            count++;

            if(arr[j] > key)
            {
                arr[j+1] = arr[j];
            }

            else
            {
                break;
            }
            
            j--;
            
        }
        arr[j+1] = key;
    }

    return count;
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

    int count = insertionsort(arr, n);

    print(arr, n);

    printf("\n%d",count);

    return 0;

}