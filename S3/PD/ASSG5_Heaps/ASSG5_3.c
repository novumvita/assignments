#include<stdio.h>

struct heap
{
    int length;
    long int* array;
};

void print(struct heap heap1)
{
    for(int i = heap1.length - 1; i >= 0; i--)                   //printing the array
    {
        printf("%ld ",heap1.array[i]);
    }
}

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

void heapsort(struct heap heap1)
{
    for(int i = heap1.length - 1; i > 0; i--)
    {
        swap(&heap1.array[i], &heap1.array[0]);
        heap1.length--;
        minheapify(heap1, 0);
    }
}

void changetokennumber(struct heap heap1, int i, long int key)
{
    heap1.array[i] = key;
    while(i > 0 && heap1.array[parent(i)] > heap1.array[i])
    {
        swap(&heap1.array[parent(i)], &heap1.array[i]);
        i = parent(i);
    }
}

void insertpatient(struct heap heap1, long int key)
{
    heap1.array[heap1.length] = 100001;
    changetokennumber(heap1, heap1.length, key);
}

void extractnextpatient(struct heap heap1)
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

void getnextpatient(struct heap heap1)
{
    if(heap1.length < 1)
    {
        printf("-1\n");
        return;
    }
    printf("%ld\n", heap1.array[0]);
}

void displayqueue(struct heap heap1)
{
    long int arr_for_sort[heap1.length];
    struct heap temp_heap;
    temp_heap.array = arr_for_sort;
    temp_heap.length = heap1.length;

    for(int i = 0; i < heap1.length; i++)
    {
        arr_for_sort[i] = heap1.array[i];
    }
    heapsort(temp_heap);
    print(temp_heap);
    printf("\n");
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
    int index;

    while(key != 's')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'i' :
                scanf("%ld", &k);
                insertpatient(heap1, k);
                heap1.length++;
                break;

            case 'e' :
                extractnextpatient(heap1);
                heap1.length--;
                break;

            case 'm' :
                getnextpatient(heap1);
                break;

            case 'c' :
                scanf("%d %ld", &i, &k);
                for(index = 0; index < heap1.length; index++)
                {
                    if(heap1.array[index] == i)
                    break;
                }
                changetokennumber(heap1, index, k);
                break;
            case 'd' :
                displayqueue(heap1);
                break;
        }
    }

    return 0;
}