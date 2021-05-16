#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    float size;
    int numPages;
    char system_id[20];
    char filename[20];
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

struct node *create_node (char *system_id, char *filename, int numPages, float size)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->numPages = numPages;
    temp->size = size;
    strcpy(temp->system_id, system_id);
    strcpy(temp->filename, filename);
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
    printf("%s\n", to_delete->system_id);
    free(to_delete);
}

void printlist (struct queue *Q)
{
    if(queue_empty(Q) == -1)
    {
        printf("-1\n");
        return;
    }
    struct node *temp = Q->head;
    while(temp != NULL)
    {
        printf("%s %s %d %.2f\n", temp->system_id, temp->filename, temp->numPages, temp->size);
        temp = temp->next;
    }
}

int main()
{
    float size;
    int numPages;
    char system_id[20];
    char filename[20];
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
            case 'a':
            scanf("%s %s %d %f", system_id, filename, &numPages, &size);
            enqueue(Q, create_node(system_id, filename, numPages, size));
            break;

            case 'e':
            dequeue(Q);
            break;

            case 'l':
            printlist(Q);
            break;
        }
    }
    return 0;
}