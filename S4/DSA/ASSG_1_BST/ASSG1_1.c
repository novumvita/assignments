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

struct q_node
{
    struct node *node;
    struct q_node *next;
};

struct queue
{
    struct q_node *head;
    struct q_node *tail;
};

void push(struct queue *Q, struct node *node)
{
    struct q_node *temp = (struct q_node *)malloc(sizeof(struct q_node));
    temp->node = node;
    temp->next = NULL;
    if(Q->head == NULL)
    {
        Q->head = temp;
        Q->tail = temp;
        return;
    }

    Q->tail->next = temp;
    Q->tail = temp;
}

struct node *pop(struct queue *Q)
{
    struct node *temp = Q->head->node;
    struct q_node *to_delete = Q->head;
    Q->head = Q->head->next;
    free(to_delete);
    return temp;
}

struct node *createNode(int k)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));

    temp->key = k;
    temp->p = NULL;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

void insert(struct tree *T, struct node *node)
{
    if(T->root == NULL)
    {
        T->root = node;
        return;
    }
    struct queue *Q = (struct queue *)malloc(sizeof(struct queue));
    Q->head = NULL;
    Q->tail = NULL;
    
    push(Q, T->root);

    while(Q->head != NULL)
    {
        struct node *temp = pop(Q);
        if(temp->left == NULL)
        {
            temp->left = node;
            return;
        }
        else
        {
            push(Q, temp->left);
        }
        if(temp->right == NULL)
        {
            temp->right = node;
            return;
        }
        else
        {
            push(Q, temp->right);
        }        
    }
}

void para_pre(struct node *node)
{
    if(node!=NULL)
 {
  printf("( %d ",node->key);
  para_pre(node->left);
  para_pre(node->right);
 }

 else
 {
     printf("( ");
 }
 printf(") ");
}

void print(struct tree *T)
{
    para_pre(T->root);
    printf("\n");
}

// void inorder(struct node *node)
// {
//  if(node!=NULL)
//  {
//   inorder(node->left);
//   printf("%d ",node->key);
//   inorder(node->right);
//  }
// }

// void preorder(struct node *node)
// {
//  if(node!=NULL)
//  {
//   printf("%d ",node->key);
//   preorder(node->left);
//   preorder(node->right);
//  }
// }

// void postorder(struct node *node)
// {
//  if(node!=NULL)
//  {
//   postorder(node->left);
//   postorder(node->right);
//   printf("%d ",node->key);
//  }
// }

int main()
{
    char c = 'c';
    int x;
    struct tree *T = (struct tree *)malloc(sizeof(struct tree));
    T->root = NULL;

    while(c != 'e')
    {
        scanf("%c", &c);
        switch(c)
        {
            case 'i':
            scanf("%d", &x);
            insert(T, createNode(x));
            break;

            case 'p':
            print(T);
            break;
        }
    }
    return 0;
}