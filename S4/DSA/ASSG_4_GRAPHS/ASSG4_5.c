#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int key;
    int distance;
    struct node* next;
};

int bellmanFord(int* graph, int source, int n)
{
    int dist[n];

    for (int i = 0; i < n; i++)
    {
        dist[i] = 10001;
    }
  
    dist[source] = 0;
  
    for (int count = 0; count < n; count++) {
        for(int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {  
                if ((dist[u] + *(graph + u*n + v)) < dist[v])
                    dist[v] = dist[u] + *(graph + u*n + v);
            }
        }
    }

    for (int count = 0; count < n; count++) {
        for(int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {  
                if ((dist[u] + *(graph + u*n + v)) < dist[v])
                    return 1;
            }
        }
    }

    return -1;
}

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

int *MatrixFromList(struct node** AdjList, int n)
{
    int *AdjMatrix = malloc(sizeof(int) * n * n);
    initialiseMatrix(AdjMatrix, n);
    for(int i = 0; i < n; i++)
    {
        struct node* curr = AdjList[i];
        while(curr != NULL)
        {
            *(AdjMatrix + i*n + curr->key) = curr->distance;
            curr = curr->next;
        }
    }
    return AdjMatrix;
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
        int j, k, dist;
        scanf("%d %d %d", &j, &k, &dist);
        AdjMatrix[j][k] = dist;
    }

    printf("%d\n", bellmanFord((int*)AdjMatrix, 0, n));

    return 0;   
}