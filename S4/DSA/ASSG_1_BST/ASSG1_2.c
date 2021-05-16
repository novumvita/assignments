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

int find_level(struct node *node, int key, int level) // Pass level = 0
{
    if(node == NULL)
    return 0;

    if(node->key == key)
    return level;

    int level_0 = find_level(node->left, key, level + 1);
    if(level_0 != 0)
    return level_0;

    level_0 = find_level(node->right, key, level + 1);
    return level_0;    
}

struct node *search(struct node *node, int key)
{
    if(node == NULL)
    return NULL;

    if(node->key == key)
    return node;

    struct node *temp = search(node->left, key);
    if(temp != NULL)
    return temp;

    return search(node->right, key);
}

int print_cousins(struct node *node, int curr_level, int level, struct node * cous)
{
    static int flag = 0;

    if(node == NULL)
    return 0;


    if(curr_level == level && node->p != cous->p)
    {
        flag = 1;
        printf("%d ", node->key);
        return 0;
    }

    print_cousins(node->left, curr_level + 1, level, cous);
    print_cousins(node->right, curr_level + 1, level, cous);
    return flag;
}

void cousins(struct tree *T, int key)
{
    int flag = print_cousins(T->root, 1, find_level(T->root, key, 1), search(T->root, key));
    if(flag == 0)
    printf("-1");
    return;
}

// void inorder(struct node *node)
// {
//  if(node!=NULL)
//  {
//   inorder(node->left);
//   printf("%d ",node->key);
//   inorder(node->right);
//  }
// }

int main()
{
    char string[1000];
    fgets(string, 1000, stdin);

    struct tree *T = (struct tree *)malloc(sizeof(struct tree));

    T->root = tree_from_para(string);

    // inorder(T->root);
    int key;
    scanf("%d", &key);
    cousins(T, key);
    return 0;
}