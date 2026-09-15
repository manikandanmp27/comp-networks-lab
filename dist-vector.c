#include <stdio.h>

#define INF 999

int main()
{
    int n, i, j, k;
    int cost[10][10], dist[10][10];

    printf("Enter number of routers: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dist[i][j] = cost[i][j];

    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    printf("\nShortest Distance Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            printf("%d ", dist[i][j]);
        printf("\n");
    }

    return 0;
}