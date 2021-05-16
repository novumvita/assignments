#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    struct node *next;
};

struct stack
{
    struct node *top;
};

struct node *create_node (int key)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

void push (struct stack *L, struct node *x)
{
    x->next = L->top;
    L->top = x;
}

void pop (struct stack *S)
{
    if(S->top == NULL)
    {
        printf("-1\n");
        return;
    }
    struct node *to_delete = S->top;
    S->top = S->top->next;
    printf("%d\n", to_delete->key);
    free(to_delete);
}

int stack_empty(struct stack *S)
{
    if(S->top == NULL)
    return -1;

    else
    return 1;
    
}

int main()
{
    struct stack Stack;
    struct stack *S = &Stack;
    S->top = NULL;
    int i;


    char key = 'x';
    while(key != 't')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'i':
            scanf("%d", &i);
            push(S, create_node(i));
            break;

            case 'd':
            pop(S);
            break;

            case 'e':
            printf("%d\n", stack_empty(S));
            break;
        }
    }
}