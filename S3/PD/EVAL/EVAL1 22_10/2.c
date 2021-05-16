#include<stdio.h>

struct student
{
    char name[20];
    float cgpa;
};

void insert(struct student *L1, int i, int n1, struct student x)
{
    for(int j = n1 - 1; j >= i; j--)
    {
        L1[j + 1] = L1[j];
    }
    L1[i] = x;
}

void combine(struct student *L1, struct student *L2, int n1, int n2)
{
    int j = 0;
    int i = 0;

    if(L2[j].cgpa < L1[i].cgpa)
    {
        insert(L1, i, n1, L2[i]);
        n1++;
        j++;
    }
    for(; i < n1; i++)
    {
        if(L2[j].cgpa >= L1[i].cgpa && (L2[j].cgpa < L1[i + 1].cgpa || i + 1 >= n1))
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

    struct student L1[100];
    struct student L2[n2];

    for(int i = 0; i < n1; i++)
    {
        scanf("%s", L1[i].name);
        scanf("%f", &L1[i].cgpa);
    }

    for(int i = 0; i < n2; i++)
    {
        scanf("%s", L2[i].name);
        scanf("%f", &L2[i].cgpa);
    }

    combine(L1, L2, n1, n2);

    for(int i = 0; i < n1 + n2; i++)
    {
        printf("%s %.2f\n", L1[i].name, L1[i].cgpa);
    }

    return 0;
}