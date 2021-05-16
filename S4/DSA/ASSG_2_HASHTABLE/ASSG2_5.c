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

struct node *maximum(struct node *x)
{
    while(x->right != NULL)
    x = x->right;

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

struct node *successor(struct tree *T, int k)
{
    struct node *temp = search(T, k);
    if(temp == NULL)
    return NULL;
    else
    return successor_node(temp);
}

int k_smallest(struct tree *T, int k)
{
    struct node *temp = minimum(T->root);
    for(int i = 0; i < k - 1; i++)
    {
        temp = successor_node(temp);
        if(temp == NULL)
        return -1;
    }
    return temp->key;
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

int k_largest(struct tree *T, int k)
{
    struct node *temp = maximum(T->root);
    for(int i = 0; i < k - 1; i++)
    {
        temp = predecessor_node(temp);
        if(temp == NULL)
        return -1;
    }
    return temp->key;
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

void inorder(struct tree *T)
{
    inorder_nodes(T->root);
    printf("\n");
}

int main()
{
    char string[1000];
    fgets(string, 1000, stdin);

    struct tree *T = (struct tree *)malloc(sizeof(struct tree));

    T->root = tree_from_para(string);

    char key = 'x';
    int x;
    struct node* node;

    while(key != 'e')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'r':
            scanf("%d", &x);
            node = predecessor(T, x);
            if(node == NULL)
            printf("-1\n");
            else
            printf("%d\n", node->key);
            break;

            case 'u':
            scanf("%d", &x);
            node = successor(T, x);
            if(node == NULL)
            printf("-1\n");
            else
            printf("%d\n", node->key);
            break;            

            case 'i':
            inorder(T);
            break;

            case 'l':
            scanf("%d", &x);
            printf("%d\n", k_largest(T, x));
            break;

            case 's':
            scanf("%d", &x);
            printf("%d\n", k_smallest(T, x));
            break;
        }
    }

    return 0;
}

//( 25 ( 13 ( ) ( 18 ( ) ( ) ) ) ( 50 ( 45 ( ) ( ) ) ( 55 ( ) ( ) ) )