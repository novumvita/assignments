#include<stdio.h>

int gcd(int x, int y)
{
    if(x < 0)
    x =- x;

    if(y < 0)
    y =- y;

    if(x == 0 && y == 0)            //invalid input
    return -1;

    if(x == 0)                      //base case
    return y;

    if(y == 0)                      //base case
    return x;
    
    if(x > y)
    return(gcd(y,x%y));

    if(y > x)
    return(gcd(x,y%x));
}

int main()
{
    int a,b;
    scanf("%d", &a);
    scanf("%d", &b);
    
    printf("%d", gcd(a,b));

    return 0;
}