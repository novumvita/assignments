#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    struct node *next;
};

struct queue
{
    struct node *head;
    struct node *tail;
};

int queue_empty(struct queue *Q)
{
    if(Q->head == NULL)
    return -1;

    else
    return 1;
}

struct node *create_node (int key)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

void enqueue (struct queue *Q, struct node *x)
{
    if(Q->head == NULL)
    {
        Q->head = x;
        Q->tail = x;
        return;
    }
    Q->tail->next = x;
    Q->tail = x;
    return;
}

void dequeue (struct queue *Q)
{
    if(queue_empty(Q) == -1)
    {
        printf("-1\n");
        return;
    }
    struct node *to_delete = Q->head;
    Q->head = Q->head->next;
    printf("%d\n", to_delete->key);
    free(to_delete);
}

int main()
{
    int i;
    struct queue Queue;
    struct queue *Q = &Queue;
    Queue.head = NULL;
    Queue.tail = NULL;
    char key = 'x';
    while(key != 't')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'i':
            scanf("%d", &i);
            enqueue(Q, create_node(i));
            break;

            case 'd':
            dequeue(Q);
            break;

            case 'e':
            printf("%d\n", queue_empty(Q));
            break;
        }
    }
    return 0;
}