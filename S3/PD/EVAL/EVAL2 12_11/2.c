#include<stdio.h>
#include<string.h>
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

int priority(char c)
{
    if( c == '*' || c == '/')
    return 2;

    else if( c == '+' || c == '-')
    return 1;

    else
    return -1;
}

struct stack_char
{
    char *A;
    int top;
    int size;
};

int stack_empty(struct stack_char *S)
{
    if(S->top == -1)
    return -1;

    else{
    return 1;}
}

int stack_full(struct stack_char *S)
{
    if(S->top == S->size - 1)
    return 1;

    else
    return 0;
}

void stack_push(struct stack_char *S, char k)
{
    if(stack_full(S) == 0)
    {
        S->top++;
        S->A[S->top] = k;
    }    
}

char stack_pop(struct stack_char *S)
{
    if(stack_empty(S) == -1)
    return -1;

    S->top--;
    return S->A[S->top+1];
}

void in_to_post(char *infix, char *postfix)
{
    int j = 0;
    char arr[20];
    struct stack_char Stack;
    struct stack_char *S = &Stack;
    S->A = arr;
    S->top = -1;
    S->size = 20;
    printf("%s\n", infix);
    for(int i = 0; infix[i] != '\0'; i++)
    {
        if(strchr("+-*/()", infix[i]) == NULL)
        {
            postfix[j] = infix[i];
            j++;
        }

        else if(infix[i] == '(')
        stack_push(S, infix[i]);

        else if(infix[i] == ')')
        {
            while(S->A[S->top] != '(')
            {
                postfix[j] = stack_pop(S);
                j++;
            }
            stack_pop(S);
        }

        else
        {
            while(priority(S->A[S->top]) >= priority(infix[i]) && stack_empty(S) != -1)
            {
                postfix[j] = stack_pop(S);
                j++;
            }
            stack_push(S, infix[i]);

        }
    }

    while(stack_empty(S) != -1)
    {
        postfix[j] = stack_pop(S);
        j++;
    }
    postfix[j] = '\0';
    // strcpy(infix, postfix);
}

struct node *create_assignment_tree(char *s)
{
    char var = s[0];
    char expr[30];
    for(int i = 2; s[i] != ';'; i++)
    expr[i-2] = s[i];
    // printf("%s\n", expr);
    char expr_post[30];

    in_to_post(expr,  expr_post);

    printf("%s\n", expr_post);

    struct node *temp1 = construct_tree(expr_post);
    
    struct node *temp2 = create_node('=', create_node(var, NULL, NULL), temp1);
    return temp2;
}

int main()
{
    FILE *input;
    fflush(stdin);
    input = fopen("input.txt", "r");
    
    char str[30];
    while(fscanf(input, "%s[^\n]", str) != EOF)
    // while(1)
    {
        fflush(stdin);
        fflush(stdout);
        printf("%s\n", str);
        // printf("%c", str[6]);
        struct ExpressionTree Tree;
        // char exp[20] = "a=b+c;";
        //scanf("%s", exp);
        Tree.root = create_assignment_tree(str);
        // Tree.root = create_assignment_tree(exp);
        inorder(Tree.root);
        printf("\n");
    }
    fclose(input);
    return 0;
}