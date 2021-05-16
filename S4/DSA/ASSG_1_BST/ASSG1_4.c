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

struct node *minimum(struct node *x)
{
    while(x->left != NULL)
    x = x->left;

    return x;
}

int min_value(struct tree *T)
{
    return minimum(T->root)->key;
}

struct node *maximum(struct node *x)
{
    while(x->right != NULL)
    x = x->right;

    return x;
}

int max_value(struct tree *T)
{
    return maximum(T->root)->key;
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

struct node *successor(struct tree *T, int k)
{
    struct node *temp = search(T, k);
    if(temp == NULL)
    return NULL;
    else
    return successor_node(temp);
}

struct node *predecessor_node(struct node *x)
{
    if(x->left != NULL)
    return maximum(x->left);

    struct node *y = x->p;

    while(y != NULL && x == y->left)
    {
        x = y;
        y = y->p;
    }
    return y;
}

struct node *predecessor(struct tree *T, int k)
{
    struct node *temp = search(T, k);
    if(temp == NULL)
    return NULL;
    else
    return predecessor_node(temp);
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
    y = successor_node(x);

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

int find_level(struct node *node, int key, int level)       //Pass level = 1 when calling
{
    if(node == NULL)
    return -1;

    if(node->key == key)
    return level;

    int level_0 = find_level(node->left, key, level + 1);
    if(level_0 != -1)
    return level_0;

    level_0 = find_level(node->right, key, level + 1);
    return level_0;    
}

int level(struct tree *T, int k)
{
    return find_level(T->root, k, 1);
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

            case 'l':
            scanf("%d", &k);
            printf("%d\n", level(T, k));
            break;

            case 'm':
            printf("%d\n", min_value(T));
            break;

            case 'x':
            printf("%d\n", max_value(T));
            break;

            case 'r':
            scanf("%d", &k);
            x = predecessor(T, k);
            if(x == NULL)
            printf("-1\n");
            else
            printf("%d\n", x->key);
            break;

            case 'u':
            scanf("%d", &k);
            x = successor(T, k);
            if(x == NULL)
            printf("-1\n");
            else
            printf("%d\n", x->key);
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