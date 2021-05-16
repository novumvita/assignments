#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int key;
    char colour;
    struct node *p;
    struct node *left;
    struct node *right;
};

struct tree
{
    struct node *root;
    struct node *null;
};

struct node *createNode(struct tree *T, int k)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));

    temp->key = k;
    temp->colour = 'R';
    temp->p = T->null;
    temp->left = T->null;
    temp->right = T->null;

    return temp;
};

struct node* leftRotate(struct tree *T, struct node* node)
{
    struct node *temp = node->right;
    node->right = temp->left;
    if(node->right != T->null)
    node->right->p = node;
    temp->p = node->p;
    if(node->p == T->null)
    T->root = temp;
    else if(node->p->left == node)
    node->p->left = temp;
    else
    node->p->right = temp;
    temp->left = node;
    node->p = temp;
    return temp;
}

struct node* rightRotate(struct tree *T, struct node* node)
{
    struct node *temp = node->left;
    node->left = temp->right;
    if(node->left != T->null)
    node->left->p = node;
    temp->p = node->p;
    if(node->p == T->null)
    T->root = temp;
    else if(node->p->left == node)
    node->p->left = temp;
    else
    node->p->right = temp;
    temp->right = node;
    node->p = temp;
    return temp;
}

void insertFixup(struct tree *T, struct node *x)
{
    while(x->p->colour == 'R')
    {
        if(x->p == x->p->p->left)
        {
            struct node *y = x->p->p->right;
            if(y->colour == 'R')
            {
                // printf("Case 11\n");
                x->p->colour = 'B';
                y->colour = 'B';
                x = x->p->p;
                x->colour = 'R';
            }
            else 
            {
                if(x == x->p->right)
                {
                    // printf("Case 22\n");
                    x = x->p;
                    leftRotate(T, x);
                }
                // printf("Case 32\n");
                x->p->colour = 'B';
                x->p->p->colour = 'R';
                rightRotate(T, x->p->p);
            }
        }
        else
        {
            struct node *y = x->p->p->left;
            if(y->colour == 'R')
            {
                // printf("Case 12\n");
                x->p->colour = 'B';
                y->colour = 'B';
                x = x->p->p;
                x->colour = 'R';
            }
            else 
            {
                if(x == x->p->left)
                {
                    // printf("Case 22\n");
                    x = x->p;
                    // printf("rightRotate not done\n");
                    rightRotate(T, x);
                    // printf("rightRotate done\n");
                }
                // printf("Case 32\n");
                x->p->colour = 'B';
                x->p->p->colour = 'R';
                leftRotate(T, x->p->p);
            }
        }
    }
    T->root->colour = 'B';
}

void insert(struct tree *T, struct node *x)
{
    struct node *y = T->null;
    struct node *z = T->root;
    while(z != T->null)
    {
        y = z;
        if(x->key < z->key)
        z = z->left;
        else
        z = z->right;
    }
    x->p = y;
    if(y == T->null)
    T->root = x;
    else if(x->key < y->key)
    y->left = x;
    else
    y->right = x;
    insertFixup(T, x);
}

void rbpara_print_recursive(struct node *null, struct node *node)
{
    if(node != null)
 {
  printf("( %d %c ", node->key, node->colour);
  rbpara_print_recursive(null, node->left);
  rbpara_print_recursive(null, node->right);
 }

 else
 {
     printf("( ");
 }
 printf(") ");
}

void printPara(struct tree *T)
{
    rbpara_print_recursive(T->null, T->root);
    printf("\n");
}

int main()
{
    struct tree *T = malloc(sizeof(struct tree));
    T->null = malloc(sizeof(struct node));
    T->null->colour = 'B';
    T->null->p = NULL;
    T->null->left = NULL;
    T->null->right = NULL;
    T->null->key = 0;
    T->root = T->null;
    char key[10] = "x";
    fgets(key, 10, stdin);
    while(key[0] != 't')
    {
        insert(T, createNode(T, atoi(key)));
        printPara(T);
        fgets(key, 10, stdin);
    }
    return 0;
}
