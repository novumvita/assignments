#include<stdio.h>
#include<stdlib.h>

struct product
{
    int product_id;
};

struct hashTable
{
    struct product** table;
    int size;
    char collisionRes;
    int c1, c2;
};

struct hashTable* HashTable(int m)      //T.table is an array of pointers to products intialised to NULL
{
    struct product** temp = (struct product**)malloc(sizeof(struct product*) * m);
    struct hashTable* T = (struct hashTable*)malloc(sizeof(struct hashTable));
    T->table = temp;
    T->size = m;
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

int isPrime(int i)
{
    for(int j = 2; j < i; j++)
    {
        if(i % j == 0)
        return 0;
    }
    return 1;
}

int smallerPrime(int m)
{
    if(m == 1)
    return 1;
    int i;
    for(i = m - 1; !isPrime(i); i--);
    return i;
}

int doubleHashing(int k, int i, int m, int R)
{
    return (((k % m) + i * (R - (k % R))) % m);
}

int hash(struct hashTable *T, int k, int i)
{
    if(T->collisionRes == 'a')
    return quadraticProbing(k, i, T->c1, T->c2, T->size);

    return doubleHashing(k, i, T->size, T->c1);
}

void insert(struct hashTable *T, int key)
{
    int i = 0;
    int hashValue = hash(T, key, i);
    while(T->table[hashValue] != NULL)
    {
        i++;
        hashValue = hash(T, key, i);
    }
    struct product* temp = (struct product*)malloc(sizeof(struct product));
    temp->product_id = key;
    T->table[hashValue] = temp;
}

int search(struct hashTable *T, int key)
{
    int i = 0;
    int hashValue = hash(T, key, i);
    int initialIndex = hashValue;
    while(T->table[hashValue] == NULL || T->table[hashValue]->product_id != key)
    {
        i++;
        hashValue = hash(T, key, i);
        if(hashValue == initialIndex)
        {
            return -1;
        }
    }
    return 1;
}

void delete(struct hashTable *T, int key)
{
    int i = 0;
    int hashValue = hash(T, key, i);
    while(T->table[hashValue]->product_id != key)
    {
        i++;
        hashValue = hash(T, key, i);
    }
    free(T->table[hashValue]);
    T->table[hashValue] = NULL;
}

void print(struct hashTable *T)
{
    for(int i = 0; i < T->size; i++)
    {
        printf("%d (", i);
        if(T->table[i] != NULL)
        printf("%d", T->table[i]->product_id);
        printf(")\n");
    }
}

int main()
{

    char collisonRes;
    scanf("%c", &collisonRes);

    int tableSize;
    scanf("%d", &tableSize);

    struct hashTable* T = HashTable(tableSize);

    char c = 'x';
    int c1, c2, x;

    if(collisonRes == 'a')         //Quadratic Probing
    {
        scanf("%d %d", &c1, &c2);
        T->c1 = c1;
        T->c2 = c2;
    }
    else
    {
        T->c1 = smallerPrime(tableSize);
    }

    T->collisionRes = collisonRes;

    while(c != 't')
    {

        scanf("%c",&c);
        switch (c)
        {
        case 'i':
            scanf("%d", &x);
            insert(T, x);
            break;

        case 's':
            scanf("%d", &x);
            printf("%d\n", search(T, x));
            break;

        case 'd':
            scanf("%d", &x);
            delete(T, x);
            break;

        case 'p':
            print(T);
            break;
        }
    }

    return 0;    
}