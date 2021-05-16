#include<stdio.h>
int count = 0;

struct heap
{
    int length;
    int* array;
};

void swap(int*x, int*y)
{
    *x=*x+*y;
    *y=*x-*y;
    *x=*x-*y;
    return;
}

void print(int arr[], int n)
{
    for(int i = 0; i < n; i++)                   //printing the array
    {
        printf("%d ",arr[i]);
    }
}

void maxheapify(struct heap heap1, int i)
{
    int l, r, largest;
    l = 2*i + 1;
    r = 2*i + 2;

    if(l < heap1.length && ++count && heap1.array[l] > heap1.array[i])
    {
        largest = l;
    }

    else
    {
        largest = i;
    }
    

    if(r < heap1.length && ++count && heap1.array[r] > heap1.array[largest])
    {
        largest = r;
    }

    if(largest != i)
    {
        swap(&heap1.array[i], &heap1.array[largest]);
        maxheapify(heap1, largest);
    }
    
}

void buildmaxheap(struct heap heap1)
{    
    for(int i = (heap1.length - 2)/2; i >= 0; i--)
    {
        maxheapify(heap1, i);
    }
}

void heapsort(struct heap heap1)
{
    buildmaxheap(heap1);

    for(int i = heap1.length - 1; i > 0; i--)
    {
        swap(&heap1.array[i], &heap1.array[0]);
        heap1.length--;
        maxheapify(heap1, 0);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int arr[n];

    struct heap heap1;
    heap1.array = arr;
    heap1.length = n;

    for( int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    heapsort(heap1);

    print(arr, n);
    printf("\n%d", count);

    return 0;
}