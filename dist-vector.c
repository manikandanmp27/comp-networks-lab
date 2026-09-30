#include<stdio.h>

int main()
{
    int n,i,j,k,change;
    int cost[10][10], dist[10][10], next[10][10];

    printf("Enter number of routers: ");
    scanf("%d",&n);

    printf("Enter cost matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&cost[i][j]);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            dist[i][j]=cost[i][j];
            next[i][j]=j;
        }

    do
    {
        change=0;

        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                for(k=0;k<n;k++)
                {
                    if(dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j]=dist[i][k]+dist[k][j];
                        next[i][j]=next[i][k];
                        change=1;
                    }
                }

    }while(change);

    for(i=0;i<n;i++)
    {
        printf("\nState value for Router %c\n",i+'A');
        printf("Dest\tNext\tDistance\n");

        for(j=0;j<n;j++)
        {
            if(dist[i][j] == 99)
                printf("%c\t-\tInfinite\n",j+'A');
            else
                printf("%c\t%c\t%d\n",
                       j+'A',next[i][j]+'A',dist[i][j]);
        }
    }

    return 0;
}
