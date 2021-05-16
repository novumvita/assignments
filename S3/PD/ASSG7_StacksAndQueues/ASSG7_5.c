#include<stdio.h>
#include<string.h>

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

int IsPalindrome(char *arr)
{
    char rev_arr[20];
    struct stack S;
    S.A = arr;
    S.size = 20;
    int i;
    for(i = 0; arr[i] != '\0'; i++);
    S.top = i - 1;

    int j = 0;
    for(; i > 0; i--)
    {
        rev_arr[j] = pop(&S);
        j++;
    }
    //printf("%s\n%s\n", arr, rev_arr);
    return strcmp(arr, rev_arr) == 0 ? 1 : 0;
}

int main()
{
    int n, i;
    n = 20;
    char arr[n];

    scanf("%s", arr);

    printf("%d\n", IsPalindrome(arr));

    return 0;
}
