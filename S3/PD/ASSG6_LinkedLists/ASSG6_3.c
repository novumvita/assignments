#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct PCB
{
    int process_id;
    char state[12];
    struct PCB *next;
};

struct PCBList
{
    struct PCB *head;
};

struct PCB *create_PCB (int process_id)
{
    struct PCB *temp;
    temp = (struct PCB*)malloc(sizeof(struct PCB));
    temp->process_id = process_id;
    temp->next = NULL;
    return temp;
}

struct PCB *list_search (struct PCBList *L, int process_id)
{
    struct PCB *temp = L->head;
    while(1)
    {
        if(temp == NULL)
        {
            return NULL;
        }

        if(temp->process_id == process_id)
        {
            return temp;
        }
        temp = temp->next;
    }
}

void insert (struct PCBList *L, struct PCB *x)
{
    x->next = L->head;
    L->head = x;
}

void delete (struct PCBList *L, struct PCB *x)
{
    if(x == NULL)
    {
        printf("-1\n");
        return;
    }
    struct PCB *temp = L->head;
    while(temp->next != x)
    {
        temp = temp->next;
    }
    struct PCB *to_delete = temp->next;
    temp->next = x->next;
    printf("%d\n", to_delete->process_id);
    free(to_delete);
}

char *get_state (int process_id, struct PCBList *L)
{
    struct PCB *temp = list_search(L, process_id);
    return temp == NULL ? "-1" : temp->state;
}

void list_waiting_processes (struct PCBList *L)
{
    if(L->head == NULL)
    {
        printf("-1\n");
        return;
    }
    int flag = 0;
    struct PCB *temp = L->head;
    while(temp != NULL)
    {
        if(strcmp(temp->state, "waiting") == 0)
        {
            printf("%d ", temp->process_id);
            flag = 1;
        }
        temp = temp->next;
    }
    if(!flag)
    printf("-1\n");
    else
    printf("\n");
    
}

void update_state (struct PCBList *L, int process_id, char *state)
{
    strcpy(list_search(L, process_id)->state, state);
}

int main()
{
    struct PCBList pcbList;
    pcbList.head = NULL;
    struct PCBList *L = &pcbList;
    char c = 'x';
    int x;
    char state[12];
    while(c != 'e')
    {
        scanf("%c", &c);
        switch(c)
        {
            case 'i':
            scanf("%d", &x);
            scanf("%s", state);
            insert(L, create_PCB(x));
            strcpy(L->head->state, state);
            break;
            case 'd':
            scanf("%d", &x);
            delete(L, list_search(L, x));
            break;
            case 'g':
            scanf("%d", &x);
            printf("%s\n", get_state(x, L));
            break;
            case 'l':
            list_waiting_processes(L);
            break;
            case 'u':
            scanf("%d", &x);
            scanf("%s", state);
            update_state(L, x, state);
            break;
        }
    }
    return 0;
}