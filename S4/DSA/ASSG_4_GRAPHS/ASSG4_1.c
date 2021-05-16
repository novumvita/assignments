#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node* next;
};

struct node **listFromMatrix(int* AdjMatrix, int n)
{
    
    struct node **AdjList = malloc(sizeof(struct node*) * n);
    for(int i = 0; i < n; i++)
    {
        AdjList[i] = malloc(sizeof(struct node));
        AdjList[i]->key = i;
        struct node *curr = AdjList[i];
        for(int j = 0; j < n; j++)
        {
            if(*(AdjMatrix + i*n + j) == 1)
            {
                curr->next = malloc(sizeof(struct node));
                curr = curr->next;
                curr->key = j;
            }
        }
        curr->next = NULL;
    }
    return AdjList;
}

void printList(struct node* node)
{
    printf("%d", node->key);
    node = node->next;
    while(node != NULL)
    {
        printf(" %d", node->key);
        node = node->next;
    }
    printf("\n");
}

void printAdjList(struct node** AdjList, int n)
{
    for(int i = 0; i < n; i++)
    {
        printList(AdjList[i]);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int AdjMatrix[n][n];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &AdjMatrix[i][j]);
        }
    }
    struct node **AdjList = listFromMatrix((int*)AdjMatrix, n);

    printAdjList(AdjList, n);

    return 0;
}