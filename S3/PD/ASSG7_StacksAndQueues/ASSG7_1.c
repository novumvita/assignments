#include<stdio.h>

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

int main()
{
    int n, i;
    scanf("%d", &n);
    int arr[n];
    struct stack S;
    S.A = arr;
    S.top = -1;
    S.size = n;
    char key = 'x';
    while(key != 't')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'i':
            scanf("%d", &i);
            push(&S, i);
            break;

            case 'd':
            printf("%d\n", pop(&S));
            break;

            case 'e':
            printf("%d\n", stack_empty(&S));
            break;
        }
    }
    return 0;
}