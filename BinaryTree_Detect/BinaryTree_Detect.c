#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <limits.h>
int adj[100][100];
int adjlen[100];
int check[100];
int V=6;
int case_=1;
int task1(int v, int parent)
{
    check[v]=1;
    int c=adjlen[v];
    //printf("%d",a);
    for(int i=0; i<c; ++i)
    {
        if (check[adj[v][i]]==0)
        {
            if (task1(adj[v][i], v))
                return 1;
        }

        else if (adj[v][i] != parent)
            return 1;
    }
    return 0;
}
void addEdge(int v,int w)
{
    int a=adjlen[v];
    //printf("%d ",a);
    int b=adjlen[w];
    adj[v][a]=w;
    adj[w][b]=v;
    adjlen[v]++;
    adjlen[w]++;
}


int isTree()
{
    for(int i=0; i<V; i++)
    {
        check[i]=0;
    }

    for (int u = 0; u < V; u++)
        if (check[u]==0)
            if (task1(u, -1))
                return 1;

    return 0;
}
void defaustate()
{
    memset(check,0,sizeof(check));
    memset(adj,0,sizeof(adj));
    memset(adjlen,0,sizeof(adjlen));


}
int main()
{
    int a,b,c=0;
    while(1)
    {
        scanf("%d",&a);
        scanf("%d",&b);
        if(a==-1&&b==-1)
        {

            break;
        }
        if(a==0&&b==0)
        {
            if(isTree()==1)
            {
                printf("%s%d%s\n","Case ",case_," is not a tree");
                case_++;

            }
            else
            {
                printf("%s%d%s\n","Case ",case_," is a tree");
                case_++;
            }
            defaustate();


        }
        addEdge(a,b);
    }


    return 0;



}
