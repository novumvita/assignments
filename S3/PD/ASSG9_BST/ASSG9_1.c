#include<stdio.h>
#include<stdlib.h>

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

struct node *minimum(struct node *x)
{
    while(x->left != NULL)
    x = x->left;

    return x;
}

struct node *maximum(struct node *x)
{
    while(x->right != NULL)
    x = x->right;

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

struct node *predecessor(struct node *x)
{
    if(x->left != NULL)
    return maximum(x->right);

    struct node *y = x->p;

    while(y != NULL && x == y->left)
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
    x->key = y->key;

    free(y);
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

void inorder_nodes(struct node *node)
{
 if(node!=NULL)
 {
  inorder_nodes(node->left);
  printf("%d ",node->key);
  inorder_nodes(node->right);
 }
}

void preorder_nodes(struct node *node)
{
 if(node!=NULL)
 {
  printf("%d ",node->key);
  preorder_nodes(node->left);
  preorder_nodes(node->right);
 }
}

void postorder_nodes(struct node *node)
{
 if(node!=NULL)
 {
  postorder_nodes(node->left);
  postorder_nodes(node->right);
  printf("%d ",node->key);
 }
}

void inorder(struct tree *T)
{
    inorder_nodes(T->root);
    printf("\n");
}

void preorder(struct tree *T)
{
    preorder_nodes(T->root);
    printf("\n");
}

void postorder(struct tree *T)
{
    postorder_nodes(T->root);
    printf("\n");
}

int main()
{
    struct tree Tree;
    Tree.root = NULL;
    struct tree *T = &Tree;

    struct node *x;

    int k;

    char key = 'a';

    while(key != 'e')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'a':
            scanf("%d", &k);
            insert(T, createNode(k));
            break;

            case 'd':
            scanf("%d", &k);
            x = search(T, k);
            if(x == NULL)
            printf("-1\n");
            else
            {
                printf("%d\n", k);
                delete(T, x);
            }
            break;

            case 's':
            scanf("%d", &k);
            x = search(T, k);
            if(x == NULL)
            printf("-1\n");
            else
            printf("1\n");
            break;

            case 'i':
            inorder(T);
            break;

            case 'p':
            preorder(T);
            break;

            case 't':
            postorder(T);
            break;
        }
    }
    return 0;
}