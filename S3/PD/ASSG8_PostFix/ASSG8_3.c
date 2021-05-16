#include<stdio.h>
#include<stdlib.h>

struct node
{
    char data;
    struct node *left;
    struct node *right;

};

struct ExpressionTree
{
    struct node *root;
};

struct node *create_node (char data, struct node *left, struct node *right)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = left;
    temp->right = right;
    return temp;
}

struct stack_node
{
    struct node *key;
    struct stack_node *next;
};

struct stack
{
    struct stack_node *top;
};

struct stack_node *stack_create_node (struct node *key)
{
    struct stack_node *temp;
    temp = (struct stack_node*)malloc(sizeof(struct stack_node));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

void push (struct stack *L, struct stack_node *x)
{
    x->next = L->top;
    L->top = x;
}

struct node *pop (struct stack *S)
{
    if(S->top == NULL)
    {
        printf("-1\n");
        return NULL;
    }
    struct stack_node *to_delete = S->top;
    S->top = S->top->next;
    return to_delete->key;
    free(to_delete);
}

int isop(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')
    return 1;

    else
    return 0;    
}

struct node *construct_tree(char *e)
{
    struct stack Stack;
    struct stack *S = &Stack;
    S->top = NULL;

    for(int i = 0; e[i] != '\0'; i++)
    {
        if(!isop(e[i]))
        {
            push(S, stack_create_node(create_node(e[i], NULL, NULL)));
        }

        else
        {
            struct node *a = pop(S);
            struct node *b = pop(S);
            push(S, stack_create_node(create_node(e[i], b, a)));
        }   
    }
    return pop(S);
}

void inorder(struct node *node)
{
 if(node!=NULL)
 {
  inorder(node->left);
  printf("%c",node->data);
  inorder(node->right);
 }
}

void preorder(struct node *node)
{
 if(node!=NULL)
 {
  printf("%c",node->data);
  preorder(node->left);
  preorder(node->right);
 }
}

void postorder(struct node *node)
{
 if(node!=NULL)
 {
  postorder(node->left);
  postorder(node->right);
  printf("%c",node->data);
 }
}

int main()
{
    struct ExpressionTree Tree;
    struct ExpressionTree *T;
    T = &Tree;
    T->root = NULL;

    char expr[20];

    char key = 'x';
    while(key != 't')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'e':
            scanf("%s", expr);
            T->root = construct_tree(expr);
            break;
            case 'i': inorder(T->root);
            printf("\n");
            break;
            case 'p': preorder(T->root);
            printf("\n");
            break;
            case 's': postorder(T->root);
            printf("\n");
            break;
        }
    }

    return 0;
}