
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<limits.h>
float data[20][2],G[20][20];
int n;
float fp1,fp2;
void adjacency()
{
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            float x1=data[i][0];
            float x2=data[j][0];
            float y1=data[i][1];
            float y2=data[j][1];
            float g1=pow((x2-x1),2);
            float g2=pow((y2-y1),2);
            G[i][j]=pow((g1+g2),0.5);
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(G[i][j]==0)
            {
                G[i][j]=9999;
            }
        }
    }
    /*for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            printf("%f ",G[i][j]);
        printf("\n");
    }
    */

}
void findans()
{

    float ans=0;
    for(int j=0; j<n; j++)
    {
        float w=9998;
        for(int i=0; i<n; i++)
        {
            if(G[i][j]<w)
                w=G[i][j];
            //printf("\n%d %d %f",i,j,G[i][j]);
        }

        //printf("%f ",w);
        if(w<8000)
            ans+=w;

    }

    ans=round(ans*1000)/1000;

    printf("%s%.3f\n","The shortest distance=",ans);




}
int main()
{

    while(1)
    {

        scanf("%d",&n);

        if(n==-1)
        {
            break;
        }
        int j=0;
        for(int i=0; i<n; i++)
        {
            scanf("%f %f",&fp1,&fp2);
            data[i][0]=fp1;
            data[i][1]=fp2;
        }
        adjacency();
        findans();









    }
}
