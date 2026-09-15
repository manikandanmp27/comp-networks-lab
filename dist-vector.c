#include <stdio.h>

int main()
{
    int n,i,j,k,change;
    int cost[10][10], dist[10][10];

    printf("Enter number of routers: ");
    scanf("%d",&n);

    printf("Enter cost matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&cost[i][j]);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            dist[i][j]=cost[i][j];

    do
    {
        change=0;

        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                for(k=0;k<n;k++)
                    if(dist[i][j] > cost[i][k]+dist[k][j])
                    {
                        dist[i][j]=cost[i][k]+dist[k][j];
                        change=1;
                    }

    }while(change);

    printf("\nDistance Vector Table:\n");
    for(i=0;i<n;i++)
    {
        printf("Router %c: ",i+'A');
        for(j=0;j<n;j++)
            printf("%d ",dist[i][j]);
        printf("\n");
    }

    return 0;
}