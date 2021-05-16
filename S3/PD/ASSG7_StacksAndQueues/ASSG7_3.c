#include<stdio.h>

struct queue
{
    int *A;
    int head;
    int tail;
    int size;
};

int queue_empty(struct queue *Q)
{
    if(Q->tail == Q->head)
    return -1;

    else
    return 1;
}

int queue_full(struct queue *Q)
{
    if(Q->tail + 1 == Q->head)
    return -1;

    else
    return 1;
}

void enqueue(struct queue *Q, int k)
{
    if(queue_full(Q) == -1)
    printf("-1\n");

    else
    {
        Q->A[Q->tail] = k;
        if(Q->tail == Q->size - 1)
        Q->tail = 0;

        else
        Q->tail++;
    }
}

int dequeue(struct queue *Q)
{
    if(queue_empty(Q) == -1)
    return -1;

    int x = Q->A[Q->head];
    if(Q->head == Q->size - 1)
    Q->head = 0;

    else
    Q->head++;    

    return x;
}

int main()
{
    int n, i;
    scanf("%d", &n);
    n++;
    int arr[n];
    struct queue Queue;
    struct queue *Q = &Queue;
    Queue.A = arr;
    Queue.head = 0;
    Queue.tail = 0;
    Queue.size = n;
    char key = 'x';
    while(key != 't')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'i':
            scanf("%d", &i);
            enqueue(Q, i);
            break;

            case 'd':
            printf("%d\n", dequeue(Q));
            break;

            case 'e':
            printf("%d\n", queue_empty(Q));
            break;

            case 'f':
            printf("%d\n", queue_full(Q));
            break;
        }
    }
    return 0;
}
