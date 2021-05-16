#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

struct node *tree_from_para(char *string)
{
    if(string[2] == ')')
    return NULL;

    int value = 0;
    int neg = 0;
    int i = 2;
    if(string[2] == '-')
    {
        neg = 1;
        i++;
    }

    value = atoi(string + i);

    for(; string[i] != ' '; i++);

    i++;

    if(neg == 1)
    value = -value;

    struct node *node = createNode(value);

    struct node *l = tree_from_para(string + i);

    int para_count = 1;
    while(para_count != 0)
    {
        i++;

        if(string[i] == ')')
        para_count--;

        else if(string[i] == '(')
        para_count++;
    }

    i += 2;

    struct node *r = tree_from_para(string + i);

    if(l != NULL)
    {
        node->left = l;
        l->p = node;
    }

    if(r != NULL)
    {
        node->right = r;
        r->p = node;
    }

    return node;
}

struct node *minimum(struct node *x)
{
    while(x->left != NULL)
    x = x->left;

    return x;
}

struct node *successor_node(struct node *x)
{
    if(x->right != NULL)
    return minimum(x->right);

    struct node *y = x->p;

    while(y != NULL && x == y->right)
    {
        x = y;
        y = y->p;
    }
    return y;
}

int k_smallest(struct tree *T, int k)
{
    struct node *temp = minimum(T->root);
    for(int i = 0; i < k - 1; i++)
    {
        temp = successor_node(temp);
    }
    return temp->key;
}

int main()
{
    char string[1000];
    fgets(string, 1000, stdin);

    struct tree *T = (struct tree *)malloc(sizeof(struct tree));

    T->root = tree_from_para(string);

    int k;
    scanf("%d", &k);

    printf("%d", k_smallest(T, k));

    return 0;
}