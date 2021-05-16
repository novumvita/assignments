#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char *word;
    struct node *next;
};

struct linkedList
{
    struct node *head;
};

struct node *create_node (char *word)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->word = (char*)malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(temp->word, word);
    temp->next = NULL;
    return temp;
}

struct node *list_search (struct linkedList *L, char *word)
{
    struct node *temp = L->head;
    while(1)
    {
        if(temp == NULL)
        {
            return NULL;
        }

        if(strcmp(word, temp->word) == 0)
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

void tableInsert(struct linkedList *T, char *str, int size)
{
    int len = strlen(str);
    int hash = (len * len) % size;
    if(list_search(&T[hash], str) == NULL)
    list_insert_tail(&T[hash], create_node(str));
}

int main()
{
    int tableSize;
    scanf("%d\n", &tableSize);
    struct linkedList hashTable[tableSize];
    for(int i = 0; i < tableSize; i++)
    {
        hashTable[i].head = NULL;
    }
    char string[500];
    scanf("%[^\n]%*c", string);
    char *token = strtok(string, " ");
    while(token != NULL)
    {
        tableInsert(hashTable, token, tableSize);
        token = strtok(NULL, " ");
    }
    for(int i = 0; i < tableSize; i++)
    {
        printf("%d:", i);
        if(hashTable[i].head == NULL)
        {
            printf("null\n");
            continue;
        }
        else
        {
            struct node *temp = hashTable[i].head;
            while(temp != NULL)
            {
                printf("%s", temp->word);
                if(temp->next == NULL)
                printf("\n");
                else
                printf("-");
                temp = temp->next;
            }
        }
    }
    return 0;
}