#include<stdio.h>
#include<stdlib.h>

struct binomialHeap
{
    struct node *head;
};

struct node
{
    int key;
    int degree;
    struct node *child;
    struct node *sibling;
    struct node *parent;
    struct node *next;
};

struct queue
{
    struct node *head;
    struct node *tail;
};

void enqueue (struct queue *Q, struct node *x)
{
    if(Q->head == NULL)
    {
        Q->head = x;
        Q->tail = x;
        return;
    }
    Q->tail->next = x;
    Q->tail = x;
    return;
}

struct node* dequeue (struct queue *Q)
{
    if(Q->head == NULL)
    {
        return NULL;
    }
    struct node *to_delete = Q->head;
    Q->head = Q->head->next;
    return to_delete;
}

void treePrint(struct node *node)
{
    struct queue *Q = malloc(sizeof(struct queue));
    Q->head = Q->tail = NULL;
    enqueue(Q, node);
    struct node *temp;
    while(Q->head != NULL)
    {
        temp = dequeue(Q);
        temp->next = NULL;
        printf("%d ", temp->key);
        temp = temp->child;
        while(temp != NULL)
        {
            enqueue(Q, temp);
            temp = temp->sibling;
        }
    }
}

void heapPrint(struct binomialHeap *H)
{
    struct node *temp = H->head;
    while(temp != NULL)
    {
        treePrint(temp);
        temp = temp->sibling;
    }
    printf("\n");
}

struct node *createNode(int k)
{
    struct node *x = (struct node*)malloc(sizeof(struct node));

    x->key = k;
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->next = NULL;
    x->degree = 0;

    return x;
}

struct binomialHeap *makeHeap()
{
    struct binomialHeap* temp = malloc(sizeof(struct binomialHeap));
    temp->head = NULL;
    return temp;
}

struct node *binomialHeapMin(struct binomialHeap *H)
{
    struct node *y = NULL;
    struct node *x = H->head;
    int min = 1000000;
    while(x != NULL)
    {
        if(x->key < min)
        {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

int minimum(struct binomialHeap *H)
{
    return binomialHeapMin(H)->key;
}

void binomialLink(struct node *y, struct node *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

struct node *binomialHeapMerge(struct binomialHeap *H1, struct binomialHeap *H2)
{
    struct node *x = H1->head;
    struct node *y = H2->head;
    free(H1);
    free(H2);
    struct node *temp = NULL;
    struct node *first = NULL;

    if(x == NULL)
    return y;
    if(y == NULL)
    return x;

    if(x->degree <= y->degree)
        {
            temp = x;
            x = x->sibling;
        }
    else
        {
            temp = y;
            y = y->sibling;
        }
    first = temp;
    while(x != NULL || y != NULL)
    {
        if(x == NULL)
        {
            temp->sibling = y;
            break;
        }
        else if(y == NULL)
        {
            temp->sibling = x;
            break;
        }
        else if(x->degree <= y->degree)
        {
            temp->sibling = x;
            x = x->sibling;
        }
        else
        {
            temp->sibling = y;
            y = y->sibling;
        }
        temp = temp->sibling;
    }
    return first;
}

struct binomialHeap *binomialHeapUnion(struct binomialHeap *H1, struct binomialHeap *H2)
{
    struct binomialHeap *H = makeHeap();
    H->head = binomialHeapMerge(H1, H2);

    if(H->head == NULL)
    return H;

    struct node *prev_x = NULL;
    struct node *x = H->head;
    struct node *next_x = x->sibling;
    while(next_x != NULL)
    {
        if((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling->degree == x->degree)))
        {
            prev_x = x;
            x = next_x;
        }
        else if(x->key <= next_x->key)
        {
            x->sibling = next_x->sibling;
            binomialLink(next_x, x);
        }
        else
        {
            if(prev_x == NULL)
                H->head = next_x;
            else
                prev_x->sibling = next_x;
            binomialLink(x, next_x);
            x = next_x;
            
        }
        next_x = x->sibling;
    }
    return H;
}

void binomialHeapInsert(struct binomialHeap **H, struct node *x)
{
    struct binomialHeap *H1 = makeHeap();
    H1->head = x;
    *H = binomialHeapUnion(*H, H1);
}

int binomialHeapExtractMin(struct binomialHeap **H)
{
    struct node *prev_min = NULL;
    struct node *min = NULL;
    struct node *x = (*H)->head;
    if(x == NULL)
    return -1;
    int minkey = x->key;
    min = x;
    while(x->sibling != NULL)
    {
        if(x->sibling->key < minkey)
        {
            minkey = x->sibling->key;
            prev_min = x;
            min = x->sibling;
        }
        x = x->sibling;
    }
    if(prev_min != NULL)
    prev_min->sibling = min->sibling;
    if((*H)->head == min)
    (*H)->head = min->sibling;
    prev_min = min->child;
    free(min);
    struct binomialHeap *H1 = makeHeap();
    if(prev_min != NULL)
    {
        min = prev_min->sibling;
        prev_min->sibling = NULL;
        while(min != NULL)
        {
            struct node *next_min = min->sibling;
            min->sibling = prev_min;
            prev_min = min;
            min = next_min;
        }
    }
    H1->head = prev_min;
    // heapPrint(H1);
    // heapPrint(*H);
    *H = binomialHeapUnion(*H, H1);
    return minkey;
}

struct node *recursiveSearch(struct node *node, int x)
{
    if(node == NULL)
    return NULL;
    else if(node->key == x)
    return node;
    struct node *temp;
    temp = recursiveSearch(node->sibling, x);
    if(temp != NULL)
    return temp;
    return recursiveSearch(node->child, x);
}

struct node *search(struct binomialHeap *H, int x)
{
    struct node *temp = H->head;
    while(temp != NULL)
    {
        struct node *res = recursiveSearch(temp, x);
        if(res != NULL)
        return res;
        temp = temp->sibling;
    }
    return NULL;
}

int binomialHeapDecreaseKey(struct binomialHeap *H, int x, int k)
{
    if(k > x)
    return -1;
    struct node *temp = search(H, x);
    if(temp == NULL)
    return -1;
    temp->key = x - k;
    struct node *p = temp->parent;
    while(p != NULL && temp->key < p->key)
    {
        temp->key = p->key;
        p->key = x - k;
        temp = p;
        p = p->parent;
    }
    return x - k;
}

int binomialHeapDecreaseKeyWithoutCondition(struct binomialHeap *H, int x, int k)
{
    struct node *temp = search(H, x);
    if(temp == NULL)
    return -1;
    temp->key = x - k;
    struct node *p = temp->parent;
    while(p != NULL && temp->key < p->key)
    {
        temp->key = p->key;
        p->key = x - k;
        temp = p;
        p = p->parent;
    }
    return x - k;
}

int binomialHeapDelete(struct binomialHeap **H, int x)
{
    if(search(*H, x) == NULL)
    return -1;
    binomialHeapDecreaseKeyWithoutCondition(*H, x, 10000);
    binomialHeapExtractMin(H);
    return x;
}

int main()
{
    char key = 'x';
    struct binomialHeap *H = makeHeap();
    int x, k;
    while(key != 'e')
    {
        scanf("%c", &key);
        switch(key)
        {
            case 'i':
            scanf("%d", &k);
            binomialHeapInsert(&H, createNode(k));
            break;

            case 'd':
            scanf("%d", &k);
            printf("%d\n", binomialHeapDelete(&H, k));
            break;

            case 'p':
            heapPrint(H);
            break;

            case 'm':
            printf("%d\n", minimum(H));
            break;

            case 'x':
            printf("%d\n", binomialHeapExtractMin(&H));
            break;

            case 'r':
            scanf("%d", &x);
            scanf("%d", &k);
            printf("%d\n", binomialHeapDecreaseKey(H, x, k));
            break;

        }
    }
    // H->head = createNode(10);
    // H->head->child = createNode(20);
    // heapPrint(H);
}