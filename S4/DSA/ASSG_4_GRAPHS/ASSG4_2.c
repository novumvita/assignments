#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int key;
    int distance;
    struct node* next;
};

struct subset {
    int parent;
    int rank;
};
 
int find(struct subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent
            = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int* popMinEdge(struct node** AdjList, int n)
{
    int min = 10001;
    int minindex = 0;
    for(int i = 0; i < n; i++)
    {
        struct node* curr = AdjList[i]->next;
        if(curr != NULL && curr->distance < min)
        {
            min = curr->distance;
            minindex = i;
        }
    }
    struct node* toPop = AdjList[minindex]->next;
    AdjList[minindex]->next = toPop->next;
    int* result = malloc(sizeof(int) * 3);
    result[0] = minindex;
    result[1] = toPop->key;
    result[2] = toPop->distance;
    free(toPop);
    return result;
}
 
int kruskalMST(struct node** AdjList, int n)
{
    int minimumCost = 0;
    struct subset* subsets = malloc(n * sizeof(struct subset));
 
    for (int v = 0; v < n; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    for(int i = 1; i < n;) {
        int* minEdge = popMinEdge(AdjList, n);
 
        int x = find(subsets, minEdge[0]);
        int y = find(subsets, minEdge[1]);
 
        if (x != y) {
            minimumCost += minEdge[2];
            Union(subsets, x, y);
            i++;
        }
        free(minEdge);
    }
 
    return minimumCost;
}

int minKey(int key[], int mstSet[], int n)
{
    int min = 10001, min_index;
  
    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
  
    return min_index;
}
  
int primMST(struct node** AdjList, int n)
{
    int parent[n];
    int key[n];
    int mstSet[n];
    int minimumCost = 0;
  
    for (int i = 0; i < n; i++)
        key[i] = 10001, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;
  
    for (int count = 0; count < n - 1; count++)
    {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;
        struct node* curr = AdjList[u];
        curr = curr->next;
        while(curr != NULL)
        {
            if(curr->distance < key[curr->key] && mstSet[curr->key] == 0)
            {
                parent[curr->key] = u;
                key[curr->key] = curr->distance;
            }
            curr = curr->next;
        }
    }
  
    for (int i = 1; i < n; i++)
    {
        minimumCost += key[i];
    }

    return minimumCost;
}
  
void swap(struct node *a, struct node *b)
{
    int tempkey = a->key;
    int tempdist = a->distance;
    a->key = b->key;
    a->distance = b->distance;
    b->key = tempkey;
    b->distance = tempdist;
}

void bubbleSort(struct node *start)
{
    int swapped, i;
    struct node *ptr1;
    struct node *lptr = NULL;
  
    if (start == NULL)
        return;
  
    do
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ptr1->distance > ptr1->next->distance)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void sortAdjList(struct node** AdjList, int n)
{
    for(int i = 0; i < n; i++)
    {
        bubbleSort(AdjList[i]->next);
    }
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
    char a;
    scanf("%c", &a);
    int n;
    scanf("%d", &n);
    struct node** AdjList = malloc(sizeof(struct node*) * n);
    int m = 0;
    char c;
    scanf("%c", &c);

    for(int i = 0; i < n; i++)
    {
        AdjList[i] = malloc(sizeof(struct node));
        AdjList[i]->next = NULL;
        AdjList[i]->key = i;
        AdjList[i]->distance = 0;
        struct node *curr = AdjList[i];
        char string[1000];
        fgets(string, 1000, stdin);
        char* token = strtok(string, " ");
        token = strtok(NULL, " ");
        while(token != NULL)
        {
            m++;
            curr->next = malloc(sizeof(struct node));
            curr = curr->next;
            curr->key = atoi(token);
            token = strtok(NULL, " ");
        }
    }

    for(int i = 0; i < n; i++)
    {
        struct node *curr = AdjList[i];
        char string[1000];
        fgets(string, 1000, stdin);
        char* token = strtok(string, " ");
        token = strtok(NULL, " ");
        while(token != NULL)
        {
            curr = curr->next;
            curr->distance = atoi(token);
            token = strtok(NULL, " ");
        }
    }

    sortAdjList(AdjList, n);
    // printAdjList(AdjList, n);

    if(a == 'a')
    printf("%d\n", kruskalMST(AdjList, n));
    else
    printf("%d\n", primMST(AdjList, n));

    return 0;   
}

/*
7
0 1 5
1 0 2 6
2 1 3
3 2 4 6
4 3 5 6
5 0 4
6 1 3 4
0 28 10
1 28 16 14
2 16 12
3 12 22 18
4 22 25 24
5 10 25
6 14 18 24
*/