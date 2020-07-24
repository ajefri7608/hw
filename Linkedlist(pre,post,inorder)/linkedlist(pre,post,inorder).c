#include <stdio.h>
char str[50],test[50];
int data[100];
int ans[50];
int top=0;
int a=0,d=0,c=0;

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

void inorder(Node *node)
{
    if(node == NULL)
    {
        return;
    }

    inorder(node->left);
    ans[d]=node->data;
    d++;
    inorder(node->right);
}

void preorder(Node *node)
{
    if(node == NULL)
    {
        return 0;
    }
    ans[d]=node->data;
    d++;
    preorder(node->left);
    preorder(node->right);
}

void postorder(Node *node)
{
    if(node == NULL)
    {
        return 0;
    }

    postorder(node->left);
    postorder(node->right);
    ans[d]=node->data;
    d++;
}

Node* insert(Node *node, int data)
{
    if(node == NULL)
    {
        Node *temp;
        temp = (Node *)malloc(sizeof(Node));
        temp -> data = data;
        temp -> left = NULL;
        temp -> right = NULL;
        return temp;
    }

    else if(data > (node->data) )
    {
        node->right = insert(node->right, data);
    }
    else if(data < (node->data))
    {
        node->left = insert(node->left, data);
    }


    return node;
}


int main()
{
    int b=-1;
    char e;
    Node *root = NULL;


    while(1)
    {
        Node *root = NULL;
        scanf("%d",&a);
        if(a==-1)
            return 0;
        for(int i=0; i<a; i++)
        {
            scanf("%d",&b);
            data[c]=b;
            c+=1;

            e=getchar();
        }
        c=0;
        for(int i=0; i<a; i++)
        {
            root = insert(root, data[i]);
        }

        preorder(root);
        printf("%s","Preorder: ");
        for(int i=0; i<d; i++)
        {
            printf("%d ",ans[i]);
        }
        memset(ans,0,sizeof(ans));

        d=0;
        printf("%c",'\n');
        inorder(root);
        printf("%s","Inorder: ");
        for(int i=0; i<d; i++)
        {
            printf("%d ",ans[i]);
        }
        memset(ans,0,sizeof(ans));
        d=0;
        printf("%c",'\n');
        postorder(root);
        printf("%s","Postorder: ");
        for(int i=0; i<d; i++)
        {
            printf("%d ",ans[i]);
        }
        memset(ans,0,sizeof(ans));
        d=0;

        printf("%c",'\n');
        memset(data,0,sizeof(data));
        printf("%c",'\n');
    }

    return 0;


}
