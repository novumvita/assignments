#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key, rank;
    struct node* p;
};

struct hashTable
{
    struct node** table;
    int size;
    // char collisionRes;
    int c1, c2;
};

int count_1, count_2, count_3, count_4;

struct hashTable* HashTable(int m)      //T.table is an array of pointers to products intialised to NULL
{
    struct node** temp = malloc(sizeof(struct node*) * m);
    struct hashTable* T = malloc(sizeof(struct hashTable));
    T->table = temp;
    T->size = m;
    T->c1 = 1;
    T->c2 = 1;
    for(int i = 0; i < m; i++)
    {
        T->table[i] = NULL;
    }
    return T;
}

int quadraticProbing(int k, int i, int c1, int c2, int m)
{
    return (((k % m) + c1 * i + c2 * i * i) % m);
}

// int doubleHashing(int k, int i, int m, int R)
// {
//     return (((k % m) + i * (R - (k % R))) % m);
// }

int hash(struct hashTable *T, int k, int i)
{
    // if(T->collisionRes == 'a')
    return quadraticProbing(k, i, T->c1, T->c2, T->size);

    // return doubleHashing(k, i, T->size, T->c1);
}

void hashInsert(struct hashTable *T, struct node* node)
{
    int i = 0;
    int hashValue = hash(T, node->key, i);
    while(T->table[hashValue] != NULL)
    {
        i++;
        hashValue = hash(T, node->key, i);
    }
    T->table[hashValue] = node;
}

struct node* hashFind(struct hashTable *T, int key)
{
    int i = 0;
    int hashValue = hash(T, key, i);
    int initialIndex = hashValue;
    while(T->table[hashValue] == NULL || T->table[hashValue]->key != key)
    {
        i++;
        hashValue = hash(T, key, i);
        if(hashValue == initialIndex)
        {
            return NULL;
        }
    }
    // printf("Found node %d\n", key);
    return T->table[hashValue];
}

void hashDelete(struct hashTable *T, int key)
{
    int i = 0;
    int hashValue = hash(T, key, i);
    while(T->table[hashValue]->key != key)
    {
        i++;
        hashValue = hash(T, key, i);
    }
    free(T->table[hashValue]);
    T->table[hashValue] = NULL;
}

struct node* makeSet(int key)
{
    struct node* temp = malloc(sizeof(struct node*));
    temp->p = temp;
    temp->key = key;
    temp->rank = 0;
    return temp;
}

struct node* findSet_1(struct node* node)
{
    count_1++;
    while(node->p != node)
    {
        count_1++;
        node = node->p;
    }
    return node;
}

struct node* findSet_2(struct node* node)
{
    count_2++;
    while(node->p != node)
    {
        count_2++;
        node = node->p;
    }
    return node;
}

struct node* findSet_3(struct node* node)
{
    count_3++;
    if(node->p != node)
    {
        node->p = findSet_3(node->p);
    }
    return node->p;
}

struct node* findSet_4(struct node* node)
{
    count_4++;
    if(node->p != node)
    {
        node->p = findSet_4(node->p);
    }
    return node->p;
}

struct node* union_1(struct node* x, struct node* y)
{
    struct node* repx = findSet_1(x);
    struct node* repy = findSet_1(y);
    return repy->p = repx;
}

struct node* union_2(struct node *x, struct node *y){
    struct node* repx = findSet_2(x);
    struct node* repy = findSet_2(y);

    if(repx == repy)
        return repx;

    if(repy->rank > repx->rank)
        return repx->p = repy;

    if(repx->rank == repy->rank)
        repx->rank++;

    return repy->p = repx;    
}

struct node* union_3(struct node* x, struct node* y)
{
    struct node* repx = findSet_3(x);
    struct node* repy = findSet_3(y);
    return repy->p = repx;
}

struct node* union_4(struct node *x, struct node *y){
    struct node* repx = findSet_4(x);
    struct node* repy = findSet_4(y);

    if(repx == repy)
        return repx;

    if(repy->rank > repx->rank)
        return repx->p = repy;

    if(repx->rank == repy->rank)
        repx->rank++;

    return repy->p = repx;    
}

int main()
{
    struct hashTable* T_1 = HashTable(256);
    struct hashTable* T_2 = HashTable(256);
    struct hashTable* T_3 = HashTable(256);
    struct hashTable* T_4 = HashTable(256);

    count_1 = 0;
    count_2 = 0;
    count_3 = 0;
    count_4 = 0;

    char switchkey = 'x';
    while(switchkey != 's')
    {
        scanf("%c", &switchkey);
        switch(switchkey)
        {
            case 'm':{
                int x;
                scanf("%d", &x);
                if(hashFind(T_1, x) != NULL){
                    printf("-1\n");
                } else {
                    struct node *set_1 = makeSet(x);
                    struct node *set_2 = makeSet(x);
                    struct node *set_3 = makeSet(x);
                    struct node *set_4 = makeSet(x);
                    printf("%d\n", x);

                    hashInsert(T_1, set_1);
                    hashInsert(T_2, set_2);
                    hashInsert(T_3, set_3);
                    hashInsert(T_4, set_4);
                }
                break;
            }
            case 'f':{
                int x;
                scanf("%d", &x);
                struct node *node_1 = hashFind(T_1, x);
                struct node *node_2 = hashFind(T_2, x);
                struct node *node_3 = hashFind(T_3, x);
                struct node *node_4 = hashFind(T_4, x);
                if(node_1 == NULL){
                    printf("-1 -1 -1 -1\n");
                } else {
                    struct node *rep_1 = findSet_1(node_1);
                    struct node *rep_2 = findSet_2(node_2);
                    struct node *rep_3 = findSet_3(node_3);
                    struct node *rep_4 = findSet_4(node_4);
                    printf("%d %d %d %d\n", rep_1->key, rep_2->key, rep_3->key, rep_4->key);
                }                  
                break;
            }
            case 'u':{
                int x, y;
                scanf("%d %d", &x, &y);
                struct node *rep_1, *rep_2, *rep_3, *rep_4,
                    *x1 = hashFind(T_1, x), *y1 = hashFind(T_1, y),
                    *x2 = hashFind(T_2, x), *y2 = hashFind(T_2, y),
                    *x3 = hashFind(T_3, x), *y3 = hashFind(T_3, y),
                    *x4 = hashFind(T_4, x), *y4 = hashFind(T_4, y);

                if(x1 == NULL || y1 == NULL){
                    printf("-1 -1 -1 -1\n");
                } else {
                    rep_1 = union_1(x1, y1);
                    // printf("union done\n");
                    rep_2 = union_2(x2, y2);
                    // printf("union done\n");
                    rep_3 = union_3(x3, y3);
                    // printf("union done\n");
                    rep_4 = union_4(x4, y4);
                    // printf("union done\n");
                    printf("%d %d %d %d\n", rep_1->key, rep_2->key, rep_3->key, rep_4->key);
                }
                break;
            }
            case 's':{
                printf("%d %d %d %d\n", count_1, count_2, count_3, count_4);
                break;
            }
        }
    }
    return 0;
}

/*
m 1
m 2
m 3
m 4
m 5
m 6
m 7
m 8
m 9
u 1 2
u 3 4
u 5 6
u 7 8
u 9 8
u 6 8
u 4 8
u 2 8
f 9
m 10
u 10 9
s
*/