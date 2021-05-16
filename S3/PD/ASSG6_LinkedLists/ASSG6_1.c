#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    struct node *next;
};

struct linkedList
{
    struct node *head;
};

struct node *create_node (int key)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

struct node *list_search (struct linkedList *L, int key)
{
    struct node *temp = L->head;
    while(1)
    {
        if(temp == NULL)
        {
            return NULL;
        }

        if(temp->key == key)
        {
            return temp;
        }
        temp = temp->next;
    }
}

void list_insert_front (struct linkedList *L, struct node *x)
{
    x->next = L->head;
    L->head = x;
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

void list_insert_after (struct linkedList *L, struct node *x, struct node *y)
{
    struct node *temp = L->head;
    while(temp->key != y->key)
    {
        temp = temp->next;
    }
    x->next = temp->next;
    temp->next = x;
}

void list_insert_before (struct linkedList *L, struct node *x, struct node *y)
{
    struct node *temp = L->head;
    if(temp == y)
    {
        list_insert_front(L, x);
        return;
    }
    while(temp->next != y)
    {
        temp = temp->next;
    }
    temp->next = x;
    x->next = y;
}

void list_delete (struct linkedList *L, struct node *x)
{
    if(x == NULL)
    {
        printf("-1\n");
        return;
    }
    struct node *temp = L->head;
    while(temp->next != x)
    {
        temp = temp->next;
    }
    struct node *to_delete = temp->next;
    temp->next = x->next;
    printf("%d\n", to_delete->key);
    free(to_delete);
}

void list_delete_first (struct linkedList *L)
{
    if(L->head == NULL)
    {
        printf("-1\n");
        return;
    }
    struct node *to_delete = L->head;
    L->head = L->head->next;
    printf("%d\n", to_delete->key);
    free(to_delete);
}

void list_delete_last (struct linkedList *L)
{
    if(L->head == NULL)
    {
        printf("-1\n");
        return;
    }
    struct node *temp = L->head;
    while(temp->next->next != NULL)
    {
        temp = temp->next;
    }
    struct node *to_delete = temp->next;
    temp->next = NULL;
    printf("%d\n", to_delete->key);
    free(to_delete);
}

int main()
{
    struct linkedList LinkedList;
    LinkedList.head = NULL;
    struct linkedList *L = &LinkedList;
    char c = 'x';
    int x, y;
    while(c != 'e')
    {
        scanf("%c", &c);
        switch(c)
        {
            case 'f':
            scanf("%d", &x);
            list_insert_front(L, create_node(x));
            break;
            case 't':
            scanf("%d", &x);
            list_insert_tail(L, create_node(x));
            break;
            case 'a':
            scanf("%d", &x);
            scanf("%d", &y);
            list_insert_after(L, create_node(x), list_search(L, y));
            break;
            case 'b':
            scanf("%d", &x);
            scanf("%d", &y);
            list_insert_before(L, create_node(x), list_search(L, y));
            break;
            case 'd':
            scanf("%d", &x);
            list_delete(L, list_search(L, x));
            break;
            case 'i':
            scanf("%d", &x);
            list_delete_first(L);
            break;
            case 'l':
            scanf("%d", &x);
            list_delete_last(L);
            break;
            case 's':
            scanf("%d", &x);
            if(list_search(L, x) == NULL)
            printf("-1\n");
            else
            printf("1\n");           
            break;            
        }
    }
    return 0;
}