#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct stack
{
    int *A;
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

void push(struct stack *S, int k)
{
    if(stack_full(S) == 0)
    {
        S->top++;
        S->A[S->top] = k;
    }    
}

int pop(struct stack *S)
{
    if(stack_empty(S) == -1)
    return -1;

    S->top--;
    return S->A[S->top+1];
}

int eval(int a, int b, char op)
{
    switch(op)
    {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
    }
}

int main()
{
    char str[200];
    scanf("%[^\n]", str);

    int arr[50];
    struct stack Stack;
    struct stack *S = &Stack;
    S->A = arr;
    S->top = -1;
    S->size = 50;

    char temp_str[10];

    int i = 0;
    while(str[i] != '\0')
    {
        if(strchr("+-*/", str[i]) != NULL)
        {
            int b = pop(S);
            int a = pop(S);
            push(S, eval(a, b, str[i]));
            i++;
        }

        else if(str[i] == ' ')
        {
            i++;
            continue;
        }

        else
        {
            char temp_str[10];
            int j = 0;
            while(str[i] != ' ' && str[i] != '\0')
            {
                temp_str[j] = str[i];
                j++;
                i++;
            } 
            temp_str[j] = '\0';
            push(S, atoi(temp_str));
        }
        
    }
    printf("%d\n", pop(S));
}