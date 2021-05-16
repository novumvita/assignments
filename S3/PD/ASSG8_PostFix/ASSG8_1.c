#include<stdio.h>
#include<string.h>

int priority(char c)
{
    if( c == '*' || c == '/')
    return 2;

    else if( c == '+' || c == '-')
    return 1;

    else
    return -1;
}

struct stack
{
    char *A;
    int top;
    int size;
};

int stack_empty(struct stack *S)
{
    if(S->top == -1)
    return -1;

    else{
    return 1;}
}

int stack_full(struct stack *S)
{
    if(S->top == S->size - 1)
    return 1;

    else
    return 0;
}

void push(struct stack *S, char k)
{
    if(stack_full(S) == 0)
    {
        S->top++;
        S->A[S->top] = k;
    }    
}

char pop(struct stack *S)
{
    if(stack_empty(S) == -1)
    return -1;

    S->top--;
    return S->A[S->top+1];
}

int main()
{
    char infix[20];
    char postfix[20];
    scanf("%s", infix);
    int j = 0;
    char arr[20];
    struct stack Stack;
    struct stack *S = &Stack;
    S->A = arr;
    S->top = -1;
    S->size = 20;
    for(int i = 0; infix[i] != '\0'; i++)
    {
        if(strchr("+-*/()", infix[i]) == NULL)
        {
            postfix[j] = infix[i];
            j++;
        }

        else if(infix[i] == '(')
        push(S, infix[i]);

        else if(infix[i] == ')')
        {
            while(S->A[S->top] != '(')
            {
                postfix[j] = pop(S);
                j++;
            }
            pop(S);
        }

        else
        {
            while(priority(S->A[S->top]) >= priority(infix[i]) && stack_empty(S) != -1)
            {
                postfix[j] = pop(S);
                j++;
            }
            push(S, infix[i]);

        }
    }

    while(stack_empty(S) != -1)
    {
        postfix[j] = pop(S);
        j++;
    }

    printf("%s\n", postfix);

    return 0;
}