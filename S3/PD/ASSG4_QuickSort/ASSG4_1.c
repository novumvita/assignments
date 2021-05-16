#include<stdio.h>

int count = 0;

int partition(int arr[], int low, int pivot_index, int high)
{
    int pivot = arr[pivot_index];
    int i = low - 1;

    int temp;

    for(int j = low; j < high; j++)
    {
        count++;
        if ( arr[j] <= pivot)
        {
            i++;
            temp = arr[i];                  //swapping arr[i] and arr[j]
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];                      //swapping arr[i + 1] and arr[high]
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quicksort(int arr[], int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = partition(arr, low, high, high);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}

void print(int arr[], int n)
{
    for(int i = 0; i < n; i++)                   //printing the array
    {
        printf("%d ",arr[i]);
    }
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

    quicksort(arr, 0, n-1);         //"high" value is included, so n-1

    print(arr, n);

    printf("\n%d", count);

    return 0;
}