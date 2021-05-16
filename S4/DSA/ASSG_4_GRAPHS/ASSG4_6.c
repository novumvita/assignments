#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct heapNode
{
    int key, degree;
    struct heapNode *p, *child, *left, *right;
    int marked;
};

struct fibonacciHeap
{
    struct heapNode *min;
    int n;
};

struct heapNodeQueue
{
    struct queueNode *head, *tail;
};

struct queueNode
{
    struct heapNode* data;
    struct queueNode *next; 
};

int isQueueEmpty(struct heapNodeQueue* Q)
{
    return Q->head == NULL && Q->tail == NULL;
}

void enqueue(struct heapNodeQueue* Q, struct heapNode *k)
{
    struct queueNode *x = malloc(sizeof(struct queueNode));
    x->data = k;
    x->next = NULL;

    if(isQueueEmpty(Q))
    {
        Q->head = Q->tail = x;
    } else 
    {
        Q->tail->next = x;
        Q->tail = x;
    }
}

struct heapNode* dequeue(struct heapNodeQueue* Q)
{
    if(isQueueEmpty(Q))
        return NULL;
    
    struct heapNode *nodeData = Q->head->data;
    struct queueNode *delNode = Q->head;
    Q->head = Q->head->next;
    if(Q->head == NULL)
    {
        Q->tail = NULL;
    }

    free(delNode);
    return nodeData;
}

struct fibonacciHeap* makeHeap()
{
    struct fibonacciHeap *temp = malloc(sizeof(struct fibonacciHeap));
    temp->min = NULL;
    temp->n = 0;
    return temp;
}

struct heapNode* createNode(int key)
{
    struct heapNode *temp = malloc(sizeof(struct heapNode));
    temp->key = key;
    temp->degree = 0;
    temp->p = temp->child = NULL;
    temp->left = temp->right = temp;
    temp->marked = 0;
    return temp;
}

struct heapNode* minimum(struct fibonacciHeap *H)
{
    return H->min;
}

void addToRootList(struct fibonacciHeap *H, struct heapNode *x)
{
    if(H->min == NULL)
    {
        H->min = x;
        x->left = x->right = x;
        return;
    }
    x->right = H->min;
    x->left = H->min->left;
    x->right->left = x;
    x->left->right = x;
}

void insert(struct fibonacciHeap *H, int x)
{
    struct heapNode *temp = createNode(x);

    addToRootList(H, temp);
    if(temp->key < H->min->key)
        H->min = temp;

    H->n++;
}

struct fibonacciHeap* fibHeapUnion(struct fibonacciHeap *H1, struct fibonacciHeap *H2)
{
    if(H1->min == NULL)
    {
        free(H1);
        return H2;
    }
    if(H2->min == NULL)
    {
        free(H2);
        return H1;
    }

    struct fibonacciHeap *H = makeHeap();
    H->min = H1->min;

    H->min->right->left = H2->min->left;
    H2->min->left->right = H->min->right;
    
    H->min->right = H2->min;
    H2->min->left = H->min;

    if(H2->min < H->min)
        H->min = H2->min;
    
    H->n = H1->n + H2->n;

    free(H1);
    free(H2);
    return H;
}

void fibHeapLink(struct fibonacciHeap *H, struct heapNode *y, struct heapNode *x)
{
    y->left->right = y->right;
    y->right->left = y->left;

    if(x->child == NULL)
    {
        y->left = y->right = y;
        x->child = y;
    }

    else 
    {
        y->left = x->child;
        y->right = x->child->right;
        y->left->right = y;
        y->right->left = y;
    }
    
    y->p = x;
    x->degree++;
    x->marked = 0;
}

void consolidate(struct fibonacciHeap *H)
{
    int Dval = log2(H->n) + 1;
    struct heapNode *A[Dval];
    for(int i = 0; i < Dval; ++i)
        A[i] = NULL;
    
    struct heapNode *w = H->min;
    do
    {
        struct heapNode *x = w, *wNext = w->right;
        int d = x->degree;

        while(A[d] != NULL)
        {
            struct heapNode *y = A[d];
            if(x->key > y->key)
            {
                y = x;
                x = A[d];
            }
            fibHeapLink(H, y, x);
            A[d] = NULL;
            ++d;
        }
        A[d] = x;
        w = wNext;
    } while (w != H->min);
    
    H->min = NULL;

    for(int i = 0; i < Dval; ++i)
    {
        if(A[i] != NULL)
        {

            addToRootList(H, A[i]);
            if(A[i]->key < H->min->key)
                H->min = A[i];
        }
    }
}

struct heapNode* extractMin(struct fibonacciHeap *H)
{
    struct heapNode *z = H->min;

    if(z == NULL)
        return NULL;

    struct heapNode *x = z->child;
    if(x != NULL)
    {
        do
        {
            struct heapNode *xNext = x->right;
            addToRootList(H, x);
            x->p = NULL;
            x = xNext;
        } while (x != z->child);
    }
    
    if(z->right == z)
    {
        H->min = NULL;
    }
    
    else 
    {
        H->min = z->right;

        z->left->right = z->right;
        z->right->left = z->left;
        consolidate(H);
    }

    H->n--;
    return z;
}

struct heapNode* search(struct heapNode *node, int x, struct heapNode *startNode)
{
    if(node == startNode)
        return NULL;

    if(node->key == x)
        return node;

    struct heapNode *result;
    result = search(node->child, x, NULL);
    if(result != NULL)
        return result;
        
    if(startNode == NULL)
    result = search(node->right, x, node);
    else
    result = search(node->right, x, startNode);

    return result;
}

struct heapNode* fibHeapSearch(struct fibonacciHeap *H, int x)
{
    struct heapNode *ptr = H->min;

    do
    {
        if(ptr->key <= x)
        {
            struct heapNode *result = search(ptr, x, NULL);
            if(result != NULL)
                return result;
        }
        ptr = ptr->right;
    } while (ptr != H->min);

    return NULL;
}

void cut(struct fibonacciHeap *H, struct heapNode *x, struct heapNode *y)
{
    if(x->right == x)
    {
        y->child = NULL;
    }
    
    else 
    {
        x->left->right = x->right;
        x->right->left = x->left;
    }

    --(y->degree);
    addToRootList(H, x);
    x->p = NULL;
    x->marked = 0;
}

void cascadingCut(struct fibonacciHeap *H, struct heapNode *y)
{
    struct heapNode *z = y->p;
    if(z == NULL)
        return;
    
    if(y->marked)
    {
        cut(H, y, z);
        cascadingCut(H, z);
    }
    
    else 
    {
        y->marked = 1;
    }
}

int fibHeapDecreaseKey(struct fibonacciHeap *H, int x, int k)
{
    struct heapNode *decreaseNode;
    if(k > x || (decreaseNode = fibHeapSearch(H, x)) == NULL)
        return -1;

    decreaseNode->key = k;
    struct heapNode *y = decreaseNode->p;

    if(y != NULL && decreaseNode->key < y->key)
    {
        cut(H, decreaseNode, y);
        cascadingCut(H, y);
    }
    if(decreaseNode->key < H->min->key)
        H->min = decreaseNode;

    return k;
}

int decreaseKey(struct fibonacciHeap *H, int x, int k)
{
    return fibHeapDecreaseKey(H, x, k);
}

int delete(struct fibonacciHeap *H, int x)
{
    fibHeapDecreaseKey(H, x, -1);
    extractMin(H);
    return x;
}

void printFibHeap(struct fibonacciHeap *H)
{
    if(H->min == NULL)
        return;
    
    // struct heapNodeQueue Q;
    // Q.head = Q.tail = NULL;

    // struct heapNode *rootPtr = H->min, *hNodePtr;

    // do
    // {
    //     enqueue(&Q, rootPtr);

    //     while((hNodePtr = dequeue(&Q)) != NULL)
    //     {
    //         printf("%d ", hNodePtr->key);

    //         if(hNodePtr->child == NULL)
    //             continue;
            
    //         hNodePtr = hNodePtr->child;
    //         struct heapNode *start = hNodePtr;
    //         do 
    //         {
    //             enqueue(&Q, hNodePtr);
    //             hNodePtr = hNodePtr->right;

    //         } while(hNodePtr != start);
    //     }
    //     rootPtr = rootPtr->right;

    // } while(rootPtr != H->min);

    struct heapNode* root = H->min;
    struct heapNode* node = H->min;
    do
    {
        printf("%d ", node->key);
        node = node->right;
    }while(node != root);

    printf("\n");
}

int main()
{
    char entered = 'x';
    int k, x;
    struct heapNode *min;

    struct fibonacciHeap *H = makeHeap();

    while(entered != 'e')
    {
        scanf("%c", &entered);
        switch (entered)
        {
            case 'i':
                scanf("%d", &k);
                insert(H, k);
                break;
            
            case 'd':
                scanf("%d", &k);
                printf("%d\n", delete(H, k));
                break;
            
            case 'p':
                printFibHeap(H);
                break;
            
            case 'm':
                min = minimum(H);
                printf("%d\n", min == NULL ? -1 : min->key);
                break;
            
            case 'x':
                min = extractMin(H);
                printf("%d\n", min == NULL ? -1 : min->key);
                break;
            
            case 'r':
                scanf("%d %d", &k, &x);
                printf("%d\n", decreaseKey(H, k, x));
                break;
            
        }
    }

    return 0;
}