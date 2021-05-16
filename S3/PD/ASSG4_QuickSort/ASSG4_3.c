#include<stdio.h>
#include<string.h>

struct Employee
{
    char name[30];

    int salary;

    int work_per_day;

    int cl;

    int lop;
};

int ComputeDeductions( struct Employee list[], int i, char ename[])
{
    for(int j = 0; j < i; j++)
    {
        if(strcmp(list[j].name, ename) == 0)
        {
            printf("%s\n", list[j].name);
            if( list[j].cl <= 5)
            return 1000*list[j].lop;

            else
            return 1000*(list[j].cl - 5 + list[j].lop);            
        }
    }
}

int insert(struct Employee list[])
{
    static int i = 0;
    //scanf("%[^\n]%*c", list[i].name);
    scanf("%s", list[i].name);
    //scanf("%d", &list[i].salary);
    list[i].salary = 30000;
    scanf("%d", &list[i].work_per_day);
    scanf("%d", &list[i].cl);
    scanf("%d", &list[i].lop);

    if(list[i].work_per_day == 8)
    {
        list[i].salary += 50;
    }

    else if(list[i].work_per_day == 10)
    {
        list[i].salary += 100;
    }

    else if(list[i].work_per_day > 10)
    {
        list[i].salary += 150;
    }

    i++;
    return i;

}

void print_noincrement(struct Employee list[], int i)
{
    for(int j = 0; j < i; j++)
    {
        if(list[j].work_per_day < 8)
        {
            printf("%s %d %d\n", list[j].name, list[j].salary, list[j].work_per_day);
        }
    }
}

void print_finalsalary(struct Employee list[], int i)
{
    for(int j = 0; j < i; j++)
    {
        printf("%s %d\n", list[j].name, list[j].salary);
    }
}

void print_workperday(struct Employee list[], int i)
{
    int x;
    scanf("%d", &x);

    for(int j = 0; j < i; j++)
    {
        if(list[j].work_per_day == x)
        {
            printf("%s %d\n", list[j].name, list[j].salary);
        }
    }
}

int main()
{
    struct Employee list[10];

    char x = 'x';

    int i = 0;

    char ename[30];

    while( x != 't')
    {
        scanf("%c", &x);
        switch (x)
        {
            case 'r': i = insert(list);
                break;
            case 'w': print_workperday(list, i);
                break;
            case 'i': print_noincrement(list, i);
                break;
            case 'f': print_finalsalary(list, i);
                break;
            case 'c':
                //scanf("%[^\n]%*c", ename);
                scanf("%s", ename);
                int ded = ComputeDeductions(list, i, ename);
                printf("%d", ded);
                break;
        }
    }

    return 0;
}