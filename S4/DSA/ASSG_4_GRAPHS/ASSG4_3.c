#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int key;
    int distance;
    struct node* next;
};

int minDistance(int dist[], int visited[], int n)
{
    int min = 10001, min_index;
  
    for (int v = 0; v < n; v++)
        if (visited[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}

int dijkstra(int* graph, int source, int target, int n)
{
    int* dist = malloc(sizeof(int) * n);
  
    int visited[n];

    for (int i = 0; i < n; i++)
    {
        dist[i] = 10001;
        visited[i] = 0;
    }
  
    dist[source] = 0;
  
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        if(u == target)
        return dist[u];
  
        visited[u] = 1;
  
        for (int v = 0; v < n; v++)
  
            if (!visited[v] && *(graph + u*n + v) && dist[u] != 10001 && (dist[u] + *(graph + u*n + v)) < dist[v])
                dist[v] = dist[u] + *(graph + u*n + v);
    }
}

int* dijkstraAll(int* graph, int source, int n)
{
    int* dist = malloc(sizeof(int) * n);
  
    int visited[n];

    for (int i = 0; i < n; i++)
    {
        dist[i] = 10001;
        visited[i] = 0;
    }
  
    dist[source] = 0;
  
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
  
        visited[u] = 1;
  
        for (int v = 0; v < n; v++)
  
            if (!visited[v] && *(graph + u*n + v) && dist[u] != 10001 && (dist[u] + *(graph + u*n + v)) < dist[v])
                dist[v] = dist[u] + *(graph + u*n + v);
    }
    return dist;
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

void allPaths(int *AdjMatrix, int source, int n)
{
    int* distance = dijkstraAll(AdjMatrix, source, n);
    if(distance[0] != 10001)
    printf(" %d", distance[0]);
    for(int i = 1; i < n; i++)
    {
        if(distance[i] != 10001)
        printf(" %d", distance[i]);
        else
        printf(" INF");
    }
    printf("\n");
}

void shortestPath(int *AdjMatrix, int source, int target, int n)
{
    int distance = dijkstra(AdjMatrix, source, target, n);
    if(distance != 10001)
    printf("%d\n", distance);
    else
    printf("UNREACHABLE\n");
}

int main()
{
    int n;
    scanf("%d", &n);
    struct node** AdjList = malloc(sizeof(struct node*) * n);
    char c;
    scanf("%c", &c);

    for(int i = 0; i < n; i++)
    {
        // printf("%d\n", i);
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
            curr->next = malloc(sizeof(struct node));
            curr = curr->next;
            curr->key = atoi(token);
            token = strtok(NULL, " ");
        }
    }
    // printf("List read\n");

    for(int i = 0; i < n; i++)
    {
        // printf("%d\n", i);
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
    // printf("List read\n");
    
    int *AdjMatrix = MatrixFromList(AdjList, n);

    char switch_key[5] = "stap";
    while(strcmp(switch_key, "stop") != 0)
    {
        switch_key[4] = '\0';
        fgets(switch_key, 5, stdin);
        if(strcmp(switch_key, "apsp") == 0)
        {
            int s;
            scanf("%d", &s);
            allPaths(AdjMatrix, s, n);
        }

        else if(strcmp(switch_key, "sssp") == 0)
        {
            int s, t;
            scanf("%d %d", &s, &t);
            shortestPath(AdjMatrix, s, t, n);
        }
    }

    return 0;   
}

/*
9
0 1 4
1 5
2 3
3 6
4
5 2 7 8
6 2
7 4
8 5 7
0 2 20
1 3
2 7
3 5
4
5 1 6 4
6 0
7 2
8 2 1
*/