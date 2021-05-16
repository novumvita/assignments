#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node* next;
};

/*************************************************************/

struct stackNode
{
    int key;
    struct stackNode *next;
};

struct stack
{
    struct stackNode *top;
};

struct stackNode *create_stack_node (int key)
{
    struct stackNode *temp;
    temp = malloc(sizeof(struct stackNode));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

void push (struct stack *S, struct stackNode *x)
{
    x->next = S->top;
    S->top = x;
}

int pop (struct stack *S)
{
    if(S->top == NULL)
    {
        printf("-1\n");
        return -1;
    }
    struct stackNode *to_delete = S->top;
    int to_return = to_delete->key;
    S->top = S->top->next;
    free(to_delete);
    return to_return;
}

int stack_empty(struct stack *S)
{
    if(S->top == NULL)
    return 1;

    else
    return 0;
}

/************************************************************/

#include<stdio.h>
#include<stdlib.h>

struct queueNode
{
    int key;
    struct queueNode *next;
};

struct queue
{
    struct queueNode *head;
    struct queueNode *tail;
};

int queue_empty(struct queue *Q)
{
    if(Q->head == NULL)
    return 1;

    else
    return 0;
}

struct queueNode *create_queue_node (int key)
{
    struct queueNode *temp;
    temp = malloc(sizeof(struct queueNode));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

void enqueue (struct queue *Q, struct queueNode *x)
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

int dequeue (struct queue *Q)
{
    if(queue_empty(Q) == 1)
    {
        return -1;
    }
    struct queueNode *to_delete = Q->head;
    int to_return = to_delete->key;
    Q->head = Q->head->next;
    free(to_delete);
    return to_return;
}

/***********************************************************/

void initialiseMatrix(int* A, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            *(A + i*n + j) = 0;
        }
    }
}

int *BFS(int *AdjMatrix, int n, int source)
{
    int* traversal = malloc(sizeof(int) * n + 1);
    int marked[n];
    for(int i = 0; i < n; i++)
    {
        marked[i] = 0;
    }
    struct queue *Q = malloc(sizeof(struct queue));
    Q->head = NULL;
    Q->tail = NULL;
    enqueue(Q, create_queue_node(source));
    int j = 1;
    while(!queue_empty(Q))
    {
        int curr_node = dequeue(Q);
        if(marked[curr_node] == 0)
        {
            marked[curr_node] = 1;
            traversal[j] = curr_node;
            j++;
            for(int i = 0; i < n; i++)
            {
                if(*(AdjMatrix + curr_node*n + i) == 1)
                {
                    if(marked[i] == 0)
                    {
                        enqueue(Q, create_queue_node(i));
                    }
                }
            }
        }
    }
    free(Q);
    traversal[0] = j - 1;
    return traversal;
}

int *DFS(int *AdjMatrix, int n, int source)
{
    int* traversal = malloc(sizeof(int) * n + 1);
    int marked[n];
    for(int i = 0; i < n; i++)
    {
        marked[i] = 0;
    }
    struct stack *S = malloc(sizeof(struct stack));
    S->top = NULL;
    push(S, create_stack_node(source));
    int j = 1;
    while(!stack_empty(S))
    {
        int curr_node = pop(S);
        if(marked[curr_node] == 0)
        {
            marked[curr_node] = 1;
            traversal[j] = curr_node;
            j++;
            for(int i = n - 1; i >= 0; i--)
            {
                if(*(AdjMatrix + curr_node*n + i) == 1)
                {
                    if(marked[i] == 0)
                    {
                        push(S, create_stack_node(i));
                    }
                }
            }
        }
    }
    free(S);
    traversal[0] = j - 1;
    return traversal;
}

void printAdjMatrix(int* A, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", *(A + i*n + j));
        }
        printf("\n");
    }
}

void printArray(int* A)
{
    printf("%d", A[1]);
    for(int i = 2; i <= A[0]; i++)
    {
        printf(" %d", A[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);
    int m;
    scanf("%d", &m);
    int AdjMatrix[n][n];
    initialiseMatrix((int*)AdjMatrix, n);

    for(int i = 0; i < m; i++)
    {
        int j;
        int k;
        scanf("%d", &j);
        scanf("%d", &k);
        AdjMatrix[j][k] = 1;
    }

    int source;
    scanf("%d", &source);

    int* BFSTraversal = BFS((int*)AdjMatrix, n, source);
    int* DFSTraversal = DFS((int*)AdjMatrix, n, source);

    printArray(BFSTraversal);
    printArray(DFSTraversal);

    return 0;
}

/*
6 8
0 1
0 2
0 3
0 4
0 5
1 3
3 5
5 4
0
0 1 2 3 4 5
0 1 3 5 4 2
6 8
0 1
1 2
2 0
2 1
2 3
2 4
2 5
5 3
0
0 1 2 3 4 5
0 1 2 3 4 5
*/