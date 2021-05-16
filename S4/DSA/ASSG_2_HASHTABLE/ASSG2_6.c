#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node
{
    int key;
    struct node *p;
    struct node *left;
    struct node *right;
};

struct tree
{
    struct node *root;
};

struct node *createNode(int k)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));

    temp->key = k;
    temp->p = NULL;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

int find_level(struct node *node, int key, int level) // Pass level = 0
{
    if(node == NULL)
    return 0;

    if(node->key == key)
    return level;

    int level_0 = find_level(node->left, key, level + 1);
    if(level_0 != 0)
    return level_0;

    level_0 = find_level(node->right, key, level + 1);
    return level_0;    
}

struct node *search(struct tree *T, int k)
{
    struct node *x = T->root;

    while(x != NULL && x->key != k)
    {
        if(k < x->key)
        x = x->left;

        else
        x = x->right;
    }
    return x;
}

void insert(struct tree *T, struct node *x)
{
    struct node *y = NULL;
    struct node *z = T->root;

    while(z != NULL)
    {
        y = z;

        if(x->key < z->key)
        z = z->left;

        else
        z = z->right;        
    }

    x->p = y;

    if(y == NULL)
    T->root = x;

    else if(x->key < y->key)
    y->left = x;

    else
    y->right = x;
}

// void inorder_nodes(struct node *node)
// {
//  if(node!=NULL)
//  {
//   inorder_nodes(node->left);
//   printf("%d ",node->key);
//   inorder_nodes(node->right);
//  }
// }

// void inorder(struct tree *T)
// {
//     inorder_nodes(T->root);
//     printf("\n");
// }

int *pathRoot(struct tree *T, int k)
{
    struct node *x = T->root;
    int *path = (int *)malloc(sizeof(int) * 100);
    int i = 0;

    while(x != NULL && x->key != k)
    {
        path[i] = x->key;
        i++;

        if(k < x->key)
        x = x->left;

        else
        x = x->right;
    }
    
    path[i] = x->key;
    return path;
}

int *pathBetween(struct tree *T, int a, int b)  //path[0] will contain path length
{
    if(a == b)
    {
        int *path = (int *)malloc(sizeof(int) * 2);
        path[0] = 1;
        path[1] = a;
        return path;
    }

    int *pathA = pathRoot(T, a);
    int *pathB = pathRoot(T, b);

    int i = 0;
    int levelA = find_level(T->root, a, 0);
    int levelB = find_level(T->root, b, 0);


    while(pathA[i] == pathB[i])
    {
        i++;
    }
    i--;
    // printf("i: %d\n", i);

    int *path = (int *)malloc(sizeof(int) * 200);
    path[0] = levelA + levelB - 2*i + 1;          //path length

    int pathIndex = 1;
    int aIndex = levelA;
    int bIndex = i;

    // printf("levelA: %d\n", levelA);
    // printf("pathA: ");
    // for(int i = 0; i < levelA + 1; i++)
    // {
    //     printf("%d ", pathA[i]);
    // }
    // printf("\n");

    // printf("levelB: %d\n", levelB);
    // printf("pathB: ");
    // for(int i = 0; i < levelB + 1; i++)
    // {
    //     printf("%d ", pathB[i]);
    // }
    // printf("\n");

    while(aIndex > i)
    {
        path[pathIndex] = pathA[aIndex];
        pathIndex++;
        aIndex--;
    }

    while(bIndex <= levelB)
    {
        path[pathIndex] = pathB[bIndex];
        pathIndex++;
        bIndex++;
    }

    return path;
}

int maxPath(struct tree *T, int a, int b)   //to include a and b,
{                                           //max = path[1] and
    int *path = pathBetween(T, a, b);       //(i = 2; i <=size)

    int size = path[0];

    int max = path[2];

    // for(int i = 0; i <= size; i++)
    // {
    //     printf("%d ", path[i]);
    // }
    // printf("\n");

    for(int i = 3; i < size; i++)
    {
        if(path[i] > max)
        max = path[i];
    }
    
    return max;
}

int main()
{
    int a, b;
    char string[1000];
    fgets(string, 1000, stdin);

    struct tree *T = (struct tree *)malloc(sizeof(struct tree *));

    char *token = strtok(string, " ");
    while(token != NULL)
    {
        insert(T, createNode(atoi(token)));
        token = strtok(NULL, " ");
    }

    // inorder(T);

    scanf("%d %d", &a, &b);

    printf("%d\n", maxPath(T, a, b));

    return 0;
}