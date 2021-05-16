#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int key;
    struct node *p;
    struct node *left;
    struct node *right;
};

struct tree
{
    struct node *root;
};

struct node *createNode(int k)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));

    temp->key = k;
    temp->p = NULL;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

struct node *tree_from_para(char *string)
{
    if(string[2] == ')')
    return NULL;

    int value = 0;
    int neg = 0;
    int i = 2;
    if(string[2] == '-')
    {
        neg = 1;
        i++;
    }

    value = atoi(string + i);

    for(; string[i] != ' '; i++);

    i++;

    if(neg == 1)
    value = -value;

    struct node *node = createNode(value);

    struct node *l = tree_from_para(string + i);

    int para_count = 1;
    while(para_count != 0)
    {
        i++;

        if(string[i] == ')')
        para_count--;

        else if(string[i] == '(')
        para_count++;
    }

    i += 2;

    struct node *r = tree_from_para(string + i);

    if(l != NULL)
    {
        node->left = l;
        l->p = node;
    }

    if(r != NULL)
    {
        node->right = r;
        r->p = node;
    }

    return node;
}

int * bst_sum(struct node *node, int value)
{
    int *temp = (int *)malloc(sizeof(int) * 3);

    if(node == NULL)
    {
        temp[0] = 0;
        temp[1] = 0;
        temp[2] = 0;
        return temp;
    }

    int *temp_l = bst_sum(node->left, value);
    int *temp_r = bst_sum(node->right, value);

    temp[2] = temp_l[2] + temp_r[2];

    if(temp_l[0] == 0 && temp_l[1] == 0 && temp_r[0] == 0 && temp_r[1] == 0)        //Both children NULL
    {
        temp[0] = 1;
        temp[1] = node->key;
    }

    if(temp_l[0] == 1 && temp_r[0] == 0 && temp_r[1] == 0 && node->key >= node->left->key)                          //Right child NULL
    {
        temp[0] = 1;
        temp[1] = temp_l[1] + node->key;
    }

    if(temp_r[0] == 1 && temp_l[0] == 0 && temp_l[1] == 0 && node->key <= node->right->key)                          //Left child NULL
    {
        temp[0] = 1;
        temp[1] = temp_r[1] + node->key;
    }

    if(temp_l[0] == 1 && temp_r[0] == 1 && node->key >= node->left->key && node->key <= node->right->key)                                            //Both BST
    {
        temp[0] = 1;
        temp[1] = temp_l[1] + temp_r[1] + node->key;
    }

    if(temp[0] == 1 && temp[1] == value)                                             //BST and sum matches
    temp[2]++;

    return temp;
}

int main()
{
    char string[1000];
    fgets(string, 1000, stdin);

    struct tree *T = (struct tree *)malloc(sizeof(struct tree));

    T->root = tree_from_para(string);

    int key;
    scanf("%d", &key);

    int ans = bst_sum(T->root, key)[2];

    if(ans == 0)
    ans -= 1;

    printf("%d", ans);

    return 0;
}