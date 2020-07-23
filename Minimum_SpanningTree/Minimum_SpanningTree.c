
#include<stdio.h>
#include<stdlib.h>

#include<limits.h>

int data[20][20],n;

int adj1[100][100];
int adj2[100][100];
int adj1len[100];
int adj2len[100];
int check[100];

int vis1[100], vis2[100];



int task2()
{
    int cost[20][20];
    int u,v,min_distance,distance[20],from[20];
    int visited[20],edge,ans,i,j;


    for(i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(data[i][j]==0)
                cost[i][j]=INT_MAX;
            else
                cost[i][j]=data[i][j];
        }

    distance[0]=0;
    visited[0]=1;

    for(int i=1; i<n; i++)
    {
        distance[i]=cost[0][i];
        from[i]=0;
        visited[i]=0;
    }

    ans=0;
    edge=n-1;

    while(edge>0)
    {
        min_distance=INT_MAX;
        for(i=1; i<n; i++)
            if(visited[i]==0&&distance[i]<min_distance)
            {
                v=i;
                min_distance=distance[i];
            }

        u=from[v];


        edge--;
        visited[v]=1;

        for(int i=1; i<n; i++)
            if(visited[i]==0&&cost[i][v]<distance[i])
            {
                distance[i]=cost[i][v];
                from[i]=v;
            }
        int vis1[n], vis2[n];
        ans=ans+cost[u][v];
    }

    return(ans);
}
void dfs1(int x)
{
    vis1[x] = 1;
    //printf("%d ",adj1len[x]);
    for (int i=0 ; i<adj1len[x]; i++)
    {
        int j=adj1[x][i];
        //printf("%d ",j);
        if(vis1[j]==0)
            dfs1(j);

    }

}


void dfs2(int x)
{
    vis2[x] = 1;

    for (int i=0 ; i<adj2len[x]; i++)
    {
        int j=adj2[x][i];
        if (vis2[j]==0)
            dfs2(j);

    }

}


int checkconnect(int n)
{

    memset(vis1, 0, sizeof vis1);
    dfs1(1);


    memset(vis2, 0, sizeof vis2);
    dfs2(1);

    for (int i = 1; i <= n; i++)
    {


        if (!vis1[i] && !vis2[i])
            return 0;
    }


    return 1;
}

void addEdge(int u,int edge)
{
    //printf("%d %d ",u,edge);
    int a=adj1len[u];
    //printf("%d ",a);
    int b=adj2len[edge];
    adj1[u][a]=edge;
    adj2[edge][b]=u;
    adj1len[u]++;
    adj2len[edge]++;
}


void defaustate()
{
    memset(check,0,sizeof(check));
    memset(adj1,0,sizeof(adj1));
    memset(adj1len,0,sizeof(adj1len));
    memset(adj2,0,sizeof(adj1));
    memset(adj2len,0,sizeof(adj1len));
    memset(data,0,sizeof(data));
    memset(vis1,0,sizeof(vis1));
    memset(vis2,0,sizeof(vis2));


}


int main()
{

    while(1)
    {
        defaustate();

        scanf("%d",&n);
        if(n==-1)
        {
            break;
        }



        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%d",&data[i][j]);


        for(int i=0; i<n; i++)
        {
            int k=0;
            for(int j=i+1; j<n; j++)
            {
                if(data[i][j]!=0)
                {
                    k++;
                    //printf("%d %d ",i+1,j+1);
                    addEdge(i+1,j+1);
                }

            }
            if(k==0)
            {
                //printf("%d %d ",i+1,i+1);
                addEdge(i+1,i+1);
            }


        }

        if(checkconnect(n)==0)
        {
            printf("%s\n","NO connected");


        }
        else
        {
            printf("%s%d\n","Minimum cost:",task2());

        }





    }
    return 0;


}


