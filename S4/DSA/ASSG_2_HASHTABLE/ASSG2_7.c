#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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

struct node *tree_from_sortarr(int *arr, int low, int high)
{
    if(low > high)
    return NULL;

    int mid = (low + high)/2;
    struct node *temp = createNode(arr[mid]);
    
    temp->left = tree_from_sortarr(arr, low, mid - 1);
    temp->right = tree_from_sortarr(arr, mid + 1, high);

    return temp;
}

void para_pre(struct node *node)
{
    if(node!=NULL)
 {
  printf("( %d ",node->key);
  para_pre(node->left);
  para_pre(node->right);
 }

 else
 {
     printf("( ");
 }
 printf(") ");
}

void recursive_level_sum(int *arr, struct node *node, int level)
{
    if(node == NULL)
    return;

    arr[level] += node->key;

    recursive_level_sum(arr, node->left, level + 1);
    recursive_level_sum(arr, node->right, level + 1);

    return;
}

int *level_sum(struct node *node, int n)
{
    int *arr = (int *)malloc(sizeof(int) * n);
    recursive_level_sum(arr, node, 0);
    return arr;
}

int find_height(struct node *node)
{
    int i = 1;
    while(node->right != NULL)
    {
        node = node->right;
        i++;
    }

    return i;
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    struct tree *T = (struct tree *)malloc(sizeof(struct tree));

    T->root = tree_from_sortarr(arr, 0, n - 1);

    para_pre(T->root);
    printf("\n");

    n = find_height(T->root);

    int *sum_arr = level_sum(T->root, n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", sum_arr[i]);
    }

    return 0;
}