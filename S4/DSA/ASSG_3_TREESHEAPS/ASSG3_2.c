#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    int height;
    int count;
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
    temp->height = 1;
    temp->count = 1;
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

int max(int a, int b)
{
    return a > b ? a : b;
}

int height(struct node *node)
{
    return node == NULL ? 0 : node->height;
}

void setHeight(struct node *node)
{
    node->height = 1 + max(height(node->left), height(node->right));
}

struct node* leftRotate(struct tree *T, struct node* node)
{
    struct node *temp = node->right;
    node->right = temp->left;
    if(node->right != NULL)
    node->right->p = node;
    temp->p = node->p;
    if(node->p == NULL)
    T->root = temp;
    else if(node->p->left == node)
    node->p->left = temp;
    else
    node->p->right = temp;
    temp->left = node;
    node->p = temp;
    setHeight(node);
    setHeight(temp);
    return temp;
}

struct node* rightRotate(struct tree *T, struct node* node)
{
    struct node *temp = node->left;
    node->left = temp->right;
    if(node->left != NULL)
    node->left->p = node;
    temp->p = node->p;
    if(node->p == NULL)
    T->root = temp;
    else if(node->p->left == node)
    node->p->left = temp;
    else
    node->p->right = temp;
    temp->right = node;
    node->p = temp;
    setHeight(node);
    setHeight(temp);
    return temp;
}

struct node* leftRightRotate(struct tree *T, struct node *node)
{
    node->left = leftRotate(T, node->left);
    node = rightRotate(T, node);
    return node;
}

struct node* rightLeftRotate(struct tree *T, struct node *node)
{
    node->right = rightRotate(T, node->right);
    node = leftRotate(T, node);
    return node;
}

int BF(struct node *node)
{
    if(node == NULL)
    return 0;
    int leftHeight = node->left == NULL ? 0 : node->left->height;
    int rightHeight = node->right == NULL ? 0 : node->right->height;
    return (leftHeight - rightHeight);
}

void para_print_recursive(struct node *node)
{
    if(node!=NULL)
 {
  printf("( %d ",node->key);
  para_print_recursive(node->left);
  para_print_recursive(node->right);
 }

 else
 {
     printf("( ");
 }
 printf(") ");
}


struct node* insert_recursive(struct tree *T, struct node *root, struct node *x)
{
    if(T->root == NULL)
    {
        T->root = x;
        return x;
    }
    if(root == NULL)
    {
        return x;
    }
    if(root->key == x->key)
    {
        root->count++;
        return root;
    }
    if(root->key > x->key)
    {
        root->left = insert_recursive(T, root->left, x);
        root->left->p = root;
        if((height(root->left) - height(root->right)) == 2) //root became left heavy
        {
            if(root->left->key > x->key)    //outside case
            root = rightRotate(T, root);
            else
            root = leftRightRotate(T, root);
        }
    }
    else if(root->key < x->key)
    {
        root->right = insert_recursive(T, root->right, x);
        root->right->p = root;
        if((height(root->left) - height(root->right)) == -2)    //root became right heavy
        {
            if(root->right->key < x->key)   //outside case
            root = leftRotate(T, root);
            else
            root = rightLeftRotate(T, root);
        }
    }
    setHeight(root);
    return root;
}

void insert(struct tree *T, int key)
{
    T->root = insert_recursive(T, T->root, createNode(key));
}

void getBalance(struct tree *T, int key)
{
    printf("%d\n", BF(search(T, key)));
}

struct node *minimum(struct node *x)
{
    while(x->left != NULL)
    x = x->left;

    return x;
}

void transplant(struct tree *T, struct node *x, struct node *y)
{
    if(x->p == NULL)
    T->root = y;
    else if(x == x->p->left)
    x->p->left= y;
    else
    x->p->right == y;
    if(y != NULL)
    y->p = x->p;
}

struct node* delete_recursive(struct tree *T, struct node *root, int key)
{
    if(root == NULL)
    return root;
    if(key < root->key)
    root->left = delete_recursive(T, root->left, key);
    else if(key > root->key)
    root->right = delete_recursive(T, root->right, key);
    else
    {
        if(root->left == NULL || root->right == NULL)
        {
            struct node *temp;
            if(root->left != NULL)
            temp = root->left;
            else
            temp = root->right;
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            transplant(T, root, temp);
            free(temp);
        }
        else
        {
            struct node *temp = minimum(root->right);
            root->key = temp->key;
            root->right = delete_recursive(T, root->right, temp->key);
        }
    }
    if(root == NULL)
    return root;
    setHeight(root);
    int balanceFactor = BF(root);
    int balanceFactorLeft = BF(root->left);
    int balanceFactorRight = BF(root->right);
    if(balanceFactor > 1)
    {
        if(balanceFactorLeft >= 0)
        return rightRotate(T, root);
        else
        return leftRightRotate(T, root);        
    }
    else if(balanceFactor < 1)
    {
        if(balanceFactorRight <= 0)
        return leftRotate(T, root);
        else
        return rightLeftRotate(T, root);
    }
    return root;
}

struct node* deleteNode(struct tree *T, int key)
{
    return delete_recursive(T, T->root, key);
}

void printPara(struct tree *T)
{
    para_print_recursive(T->root);
    printf("\n");
}

void inorder_multi_recursive(struct node *node)
{
 if(node!=NULL)
 {
  inorder_multi_recursive(node->left);
  for(int i = 0; i < node->count; i++)
  printf("%d ",node->key);
  inorder_multi_recursive(node->right);
 }
}

int main()
{
    struct tree *T = malloc(sizeof(struct tree));
    T->root = NULL;
    int n, x;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        insert(T, x);
    }
    inorder_multi_recursive(T->root);
    return 0;
}