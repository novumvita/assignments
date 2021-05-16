#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int model_number;
    int price;
    char model_name[20];
    struct node *p;
    struct node *left;
    struct node *right;
};

struct tree
{
    struct node *root;
};

struct node *createNode(int n, char *s, int p)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));

    temp->model_number = n;
    strcpy(temp->model_name, s);
    temp->price = p;
    temp->p = NULL;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

struct node *minimum(struct node *x)
{
    while(x->left != NULL)
    x = x->left;

    return x;
}

struct node *successor(struct node *x)
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

void insert(struct tree *T, struct node *x)
{
    struct node *y = NULL;
    struct node *z = T->root;

    while(z != NULL)
    {
        y = z;

        if(x->model_number < z->model_number)
        z = z->left;

        else
        z = z->right;        
    }

    x->p = y;

    if(y == NULL)
    T->root = x;

    else if(x->model_number < y->model_number)
    y->left = x;

    else
    y->right = x;
}

void delete(struct tree *T, struct node *x)
{
    struct node *y, *z;

    if(x->left == NULL || x->right == NULL)
    y = x;

    else
    y = successor(x);

    if(y->left != NULL)
    z = y->left;

    else
    z = y->right;

    if(z != NULL)
    z->p = y->p;

    if(y->p == NULL)
    T->root = z;

    else if(y->p->left == y)
    y->p->left = z;

    else
    y->p->right = z;

    if(y != x)
    {
        x->model_number = y->model_number;
        x->price = y->price;
        strcpy(x->model_name, y->model_name);
    }

    free(y);
}

struct node *search(struct tree *T, int k)
{
    struct node *x = T->root;

    while(x != NULL && x->model_number != k)
    {
        if(k < x->model_number)
        x = x->left;

        else
        x = x->right;
    }
    return x;
}

void inorder_nodes(struct node *node)
{
 if(node!=NULL)
 {
  inorder_nodes(node->left);
  printf("%d %s %d\n", node->model_number, node->model_name, node->price);
  inorder_nodes(node->right);
 }
}

void inorder(struct tree *T)
{
    inorder_nodes(T->root);
}

void modify(struct tree *T, int k, int p)
{
    struct node *x = search(T, k);
    x->price = p;
}

int main()
{
    struct tree Tree;
    Tree.root = NULL;
    struct tree *T = &Tree;

    struct node *x;

    int k;
    char s[20];
    int p;

    char key = 'a';

    while(key != 'e')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'a':
            scanf("%d %s %d", &k, s, &p);
            insert(T, createNode(k, s, p));
            break;

            case 'd':
            scanf("%d", &k);
            x = search(T, k);
            if(x == NULL)
            printf("-1\n");
            else
            {
                printf("%d %s %d\n", x->model_number, x->model_name, x->price);
                delete(T, x);
            }
            break;

            case 's':
            scanf("%d", &k);
            x = search(T, k);
            if(x == NULL)
            printf("-1\n");
            else
            printf("%d %s %d\n", x->model_number, x->model_name, x->price);
            break;

            case 'i':
            inorder(T);
            break;

            case 'm':
            scanf("%d %d", &k, &p);
            modify(T, k, p);
            break;
        }
    }
    return 0;
}