#include<stdio.h>

int count = 0;

int  merge(int arr[], int low, int mid, int high)
{
    int inversion_count = 0;
    int n1 = mid - low + 2;
    int n2 = high - mid + 1;

    int arr_1[n1];
    int arr_2[n2];

    for (int i = 0; i < n1 - 1; i++)    //assigning to sub-array 1
    {
        arr_1[i] = arr[low + i];
    }
    arr_1[n1 - 1] = 20000;          //sentinal

    for (int i = 0; i < n2 - 1; i++)    //assigning to sub-array 2
    {
        arr_2[i] = arr[mid + 1 + i];
    }
    arr_2[n2 - 1] = 20000;          //sentinal

    int j = 0;

    /*for(int i = 0; i < n1 - 1; i++)     //counting inversions
    {
        while(j < n2 - 1)
        {
            if(arr_1[i] > arr_2[j])
            inversion_count += 1;
        }
    }
*/
    for(int i=0, j=0, k=low; k < high + 1; k++)
    {
        count++;
        
        if (arr_1[i] <= arr_2[j])
        {
            arr[k] = arr_1[i];
            i++;
        }
        else
        {
            arr[k] = arr_2[j]; 
            j++;
            inversion_count += n1 - 1 - i;
        }
    }

    return inversion_count;
}


int mergesort(int arr[], int low, int high)
{
    int inversion_count = 0;
    if(low < high)
    {
        int mid = (low + high) / 2;
        inversion_count += mergesort(arr, low, mid);
        inversion_count += mergesort(arr, mid + 1, high);

        inversion_count += merge(arr, low, mid, high);
    }
    return inversion_count;
}

void print(int arr[], int n)
{
    for(int i=0;i<n;i++)                   //printing the array
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

    /*int inversion_count = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            inversion_count++;
        }
    }*/

    int inversion_count = mergesort(arr, 0, n-1);         //"high" value is included, so n-1

    print(arr, n);

    //printf("\n%d", count);
    printf("\n%d", inversion_count);

    return 0;
}
