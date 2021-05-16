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

struct tree *combine1(int k, struct tree *T1, struct tree *T2)
{
    struct tree Tree3;
    Tree3.root = NULL;
    struct tree *T3 = &Tree3;

    T3->root = createNode(k);
    T3->root->left = T1->root;
    T3->root->right = T2->root;

    T1->root = NULL;
    T2->root = NULL;

    return T3;
}

struct tree *combine2(struct tree *T1, struct tree *T2)
{
    if(T1->root == NULL)
    return T2;

    struct node *temp = maximum(T1->root);
    int temp_key = temp->key;
    if(temp->p != NULL)
    temp->p->right = NULL;

    free(temp);

    return combine1(temp_key, T1, T2);
}

int main()
{
    struct tree Tree1;
    Tree1.root = NULL;
    struct tree *T1 = &Tree1;

    struct tree Tree2;
    Tree2.root = NULL;
    struct tree *T2 = &Tree2;
    
    char c;

    int k;

    do
    {
        scanf("%c", &c);
        if(c != ' ' && c != '\n')
        {
            char temp_str[10];
            int j = 0;
            while(c != ' ' && c != '\n')
            {
                temp_str[j] = c;
                j++;
                scanf("%c", &c);
            } 
            temp_str[j] = '\0';
            insert(T1, createNode(atoi(temp_str)));
        }
    }while(c != '\n');

    do
    {
        scanf("%c", &c);
        if(c != ' ' && c != '\n')
        {
            char temp_str[10];
            int j = 0;
            while(c != ' ' && c != '\n')
            {
                temp_str[j] = c;
                j++;
                scanf("%c", &c);
            } 
            temp_str[j] = '\0';
            insert(T2, createNode(atoi(temp_str)));
        }
    }while(c != '\n');

    // scanf("%d", &k);
    // inorder(combine1(k, T1, T2));

    inorder(combine2(T1, T2));

    return 0;
}