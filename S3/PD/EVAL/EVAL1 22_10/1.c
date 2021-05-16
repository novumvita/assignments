#include<stdio.h>

void insert(float *L1, int i, int n1, float x)
{
    for(int j = n1 - 1; j >= i; j--)
    {
        L1[j + 1] = L1[j];
    }
    L1[i] = x;
}

void combine(float *L1, float *L2, int n1, int n2)
{
    int j = 0;
    int i = 0;

    if(L2[j] < L1[i])
    {
        insert(L1, i, n1, L2[i]);
        n1++;
        j++;
    }
    for(; i < n1; i++)
    {
        if(L2[j] >= L1[i] && (L2[j] < L1[i + 1] || i + 1 >= n1))
        {
            insert(L1, i + 1, n1, L2[j]);
            n1++;
            j++;
        }
    }
}

int main()
{
    int n1, n2;
    scanf("%d", &n1);
    scanf("%d", &n2);

    float L1[100];
    float L2[n2];

    for(int i = 0; i < n1; i++)
    {
        scanf("%f", &L1[i]);
    }

    for(int i = 0; i < n2; i++)
    {
        scanf("%f", &L2[i]);
    }

    combine(L1, L2, n1, n2);

    for(int i = 0; i < n1 + n2; i++)
    {
        printf("%.2f ", L1[i]);
    }

    return 0;
}