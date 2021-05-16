#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    float cgpa;
    char name[20];
    struct node *next;
};

struct linkedList
{
    struct node *head;
};

struct node *create_node (float cgpa, char *name)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->cgpa = cgpa;
    strcpy(temp->name, name);
    temp->next = NULL;
    return temp;
}

void list_insert_after (struct linkedList *L, struct node *x, struct node *y)
{
    struct node *temp = L->head;
    while(temp->cgpa != y->cgpa)
    {
        temp = temp->next;
    }
    x->next = temp->next;
    temp->next = x;
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

void combine(struct linkedList *L1, struct linkedList *L2)
{
    struct node *L1_element = L1->head;
    struct node *L2_element = L2->head;

    if(L2_element->cgpa < L1_element->cgpa)
    {
        list_insert_front(L1, create_node(L2_element->cgpa, L2_element->name));
        L2_element = L2_element->next;
        L1_element = L1->head;
    }
    
    while (L2_element != NULL)
    {
        if(L2_element->cgpa >= L1_element->cgpa && (L1_element->next == NULL || L2_element->cgpa < L1_element->next->cgpa))
        {
            list_insert_after(L1, create_node(L2_element->cgpa, L2_element->name), L1_element);
            L2_element = L2_element->next;
        }
        L1_element = L1_element->next;
    }
}

int main()
{
    int n1, n2;
    scanf("%d", &n1);
    scanf("%d", &n2);

    struct linkedList List1;
    List1.head = NULL;
    struct linkedList List2;
    List2.head = NULL;

    struct linkedList *L1 = &List1;
    struct linkedList *L2 = &List2;

    float cgpa;
    char name[20];

    for(int i = 0; i < n1; i++)
    {
        scanf("%s", name);
        scanf("%f", &cgpa);
        list_insert_tail(L1, create_node(cgpa, name));
    }

    for(int i = 0; i < n2; i++)
    {
        scanf("%s", name);
        scanf("%f", &cgpa);
        list_insert_tail(L2, create_node(cgpa, name));
    }
    
    combine(L1, L2);

    struct node *temp = L1->head;

    for(int i = 0; i < n1 + n2; i++)
    {
        printf("%s %.2f\n", temp->name, temp->cgpa);
        temp = temp->next;
    }

    return 0;
}