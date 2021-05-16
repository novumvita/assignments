#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char *string;
    struct node *next;
};

struct linkedList
{
    struct node *head;
};

struct node *create_node (char *string)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->string = (char*)malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(temp->string, string);
    temp->next = NULL;
    return temp;
}

struct node *list_search (struct linkedList *L, char *string)
{
    struct node *temp = L->head;
    while(1)
    {
        if(temp == NULL)
        {
            return NULL;
        }

        if(strcmp(string, temp->string) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
}

void list_insert_tail (struct linkedList *L, struct node *x)
{
    if(L->head == NULL)
    {
        L->head = x;
        return;
    }
    struct node *temp = L->head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = x;
    return;
}

int power(int n)
{
    int res = 1;
    for(int i = 0; i < n; i++)
    res *= 2;
    return res;
}

void list_insert_front (struct linkedList *L, struct node *x)
{
    x->next = L->head;
    L->head = x;
}

void list_insert_before (struct linkedList *L, struct node *x, struct node *y)
{
    struct node *temp = L->head;
    if(temp == y)
    {
        x->next = L->head;
        L->head = x;
        return;
    }
    while(temp->next != y)
    {
        temp = temp->next;
    }
    temp->next = x;
    x->next = y;
}

void list_insert_after (struct linkedList *L, struct node *x, struct node *y)
{
    struct node *temp = L->head;
    while(temp != y)
    {
        temp = temp->next;
    }
    x->next = temp->next;
    temp->next = x;
}

int findHash(char *str)
{
    int len = strlen(str);
    int flags[8];
    for(int i = 0; i < 8; i++)
    {
        flags[i] = 0;
    }
    for(int i = 0; i < len; i++)
    {
        flags[(int)str[i] - 97] = flags[(int)str[i] - 97] + 1;
    }
    int hash = 0;
    for(int i = 0; i < 8; i++)
    {
        if(flags[i] > 0)
        {
            hash += power(i);
        }
    }
    return hash;
}

void tableInsert(struct linkedList *T, char *str)
{
    int len = strlen(str);
    int hash = findHash(str);
    struct node *temp = T[hash].head;
    if(temp == NULL || strcmp(temp->string, str) > 0)
    {
        list_insert_front(&T[hash], create_node(str));
        return;
    }
    while(temp != NULL && strcmp(temp->string, str) < 0)
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        list_insert_tail(&T[hash], create_node(str));
        return;
    }
    list_insert_before(&T[hash], create_node(str), temp);
    return;
}

void printList(struct linkedList *L)
{
    struct node *temp = L->head;
    while(temp != NULL)
    {
        if(temp != L->head)
        printf(" ");
        
        printf("%s", temp->string);
        if(temp->next == NULL)
        {
            printf("\n");
            break;
        }
        temp = temp->next;
    }
}

int main()
{
    int tableSize = 256;
    struct linkedList hashTable[tableSize];
    for(int i = 0; i < tableSize; i++)
    {
        hashTable[i].head = NULL;
    }
    int n;
    scanf("%d\n", &n);
    char string[51];
    for(int i = 0; i < n; i++)
    {
        scanf("%[^\n]%*c", string);
        tableInsert(hashTable, string);
    }
    for(int i = 0; i < tableSize; i++)
    {
        printList(&hashTable[i]);
    }
    return 0;
}