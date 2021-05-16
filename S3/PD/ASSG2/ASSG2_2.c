#include<stdio.h>

long int fact( long int n)
{
    return n<2? 1 : n*fact(n-1);
}

int main()
{
    long int x;
    scanf("%ld" , &x);

    printf("%ld" , fact(x));

    return 0;
}