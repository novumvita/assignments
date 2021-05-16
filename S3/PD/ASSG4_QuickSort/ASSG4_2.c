#include<stdio.h>
#include<string.h>

int main()
{
    char str[50];

    char query[20];

    fgets(str, 50, stdin);

    fgets(query, 20, stdin);

    int n1 = strlen(str);

    //printf("%d\n", n1);

    int n2 = strlen(query);

    //printf("%d\n", n2);

    int flag = 0;

    int i;

    for(i = 0; i < n1 - n2 + 1; i++)
    {
        if(str[i] == query[0])
        {
            flag = 1;
            for(int j = 1; j < n2 - 1; j++)
            {
                if(str[i + j] != query[j])
                {
                    flag = 0;
                    break;
                }                
            }
        }

        if(flag)
        break;
    }

    if(flag)
    printf("%d", i);

    else
    printf("-1");

    return 0;
    
}