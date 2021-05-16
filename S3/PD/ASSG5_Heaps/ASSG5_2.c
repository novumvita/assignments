#include<stdio.h>

struct heap
{
    int length;
    long int* array;
};

int parent(int child)
{
    return (child - 1)/2;
}

void swap(long int*x, long int*y)
{
    *x=*x+*y;
    *y=*x-*y;
    *x=*x-*y;
    return;
}

void minheapify(struct heap heap1, int i)
{
    int l, r, smallest;
    l = 2*i + 1;
    r = 2*i + 2;

    if(l < heap1.length && heap1.array[l] < heap1.array[i])
    {
        smallest = l;
    }

    else
    {
        smallest = i;
    }
    

    if(r < heap1.length && heap1.array[r] < heap1.array[smallest])
    {
        smallest = r;
    }

    if(smallest != i)
    {
        swap(&heap1.array[i], &heap1.array[smallest]);
        minheapify(heap1, smallest);
    }
    
}

void heapdecreasekey(struct heap heap1, int i, long int key)
{
    heap1.array[i] = key;
    while(i > 0 && heap1.array[parent(i)] > heap1.array[i])
    {
        swap(&heap1.array[parent(i)], &heap1.array[i]);
        i = parent(i);
    }
}

void minheapinsert(struct heap heap1, long int key)
{
    heap1.array[heap1.length] = 100001;
    heapdecreasekey(heap1, heap1.length, key);
}

void heapextractmin(struct heap heap1)
{
    if(heap1.length < 1)
    {
        printf("-1\n");
        return;
    }
    int min = heap1.array[0];
    heap1.array[0] = heap1.array[heap1.length - 1];
    minheapify(heap1, 0);
    printf("%d\n", min);
}

void heapminimum(struct heap heap1)
{
    printf("%ld\n", heap1.array[0]);
}

int main()
{
    char key = 'k';

    long int arr[1000];

    struct heap heap1;
    heap1.array = arr;
    heap1.length = 0;
    
    int i = 0;
    long int k = 0;

    while(key != 's')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'i' :
                scanf("%ld", &k);
                minheapinsert(heap1, k);
                heap1.length++;
                break;

            case 'e' :
                heapextractmin(heap1);
                heap1.length--;
                break;

            case 'm' :
                heapminimum(heap1);
                break;

            case 'd' :
                scanf("%d %ld", &i, &k);
                heapdecreasekey(heap1, i, k);
                break;
        }
    }

    return 0;
}