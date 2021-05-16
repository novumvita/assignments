#include<stdio.h>

int sum(int array[], int size)
{
    int sum = 0;

    for(int i = 0; i < size; i++)
    {
        sum += array[i];
    }

    return sum;
}

int degree(int n, int edge[][n], int i, int node_active[])
{
    int degree = 0;

    for(int j = 0; j < n; j++)
    {
        if(edge[i][j] == 1 && node_active[j] == 1)
        {
            degree += 1;
        }
    }
    
    return degree;
}

void six_colour(int node_count, char node[], int node_active[], int edge[][node_count])
{
    if(sum(node_active, node_count) == 1)
    {
        for(int i = 0; i < node_count; i++)
        {
            if(node_active[i] == 1)
            {
                node[i] = 'a';
                return;
            }
        }
    }

    int i;

    for(i = 0; i < node_count; i++)
    {
        if(node_active[i] == 1 && degree(node_count, edge, i, node_active) <= 5)
        {
            node_active[i] = 0;
            six_colour(node_count, node, node_active, edge);
            break;
        }
    }

    node_active[i] = 1;

    int neighbour_colour[6] = {0, 0, 0, 0, 0, 0};

    for(int j = 0; j < node_count; j++)
    {
        if( edge[i][j] == 1 && node_active[j] == 1)
        {
            switch(node[j])
            {
                case 'a': neighbour_colour[0] = 1;
                break;
                case 'b': neighbour_colour[1] = 1;
                break;
                case 'c': neighbour_colour[2] = 1;
                break;
                case 'd': neighbour_colour[3] = 1;
                break;
                case 'e': neighbour_colour[4] = 1;
                break;
                case 'f': neighbour_colour[5] = 1;
                break;
            }
        }
    }

    if(neighbour_colour[0] == 0)
    node[i] = 'a';

    else if(neighbour_colour[1] == 0)
    node[i] = 'b';

    else if(neighbour_colour[2] == 0)
    node[i] = 'c';

    else if(neighbour_colour[3] == 0)
    node[i] = 'd';

    else if(neighbour_colour[4] == 0)
    node[i] = 'e';

    else if(neighbour_colour[5] == 0)
    node[i] = 'f';

    return;

}

int main()
{
    int node_count;
    scanf("%d", &node_count);

    char node[node_count];

    int node_active[node_count];
    for(int i = 0; i < node_count; i++)
    {
        node_active[i] = 1;
    }

    int edge_count;
    scanf("%d", &edge_count);

    int i, j;

    int edge[node_count][node_count];
    for(i = 0; i < node_count; i++)
    {
        for(j = 0; j < node_count; j++)
        {
            edge[i][j] = 0;
        }
    }

    for(int x = 0; x < edge_count; x++)
    {
        scanf("%d", &i);
        scanf("%d", &j);

        edge[i][j] = 1;
        edge[j][i] = 1;
    }

    six_colour(node_count, node, node_active, edge);

    for(i = 0; i < node_count; i++)
    {
        printf("%c\n", node[i]);
    }

    return 0;
    
}