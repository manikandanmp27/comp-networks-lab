#include <stdio.h>

#define MAX 10
#define INF 99

int cost[MAX][MAX], dist[MAX][MAX], next[MAX][MAX], n;

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    // Step 1: Read the direct link cost matrix
    printf("Enter the cost matrix (99 for no link):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            // Step 2: Initialize distance table with direct costs and next-hop to destination itself
            dist[i][j] = cost[i][j];
            next[i][j] = j;
        }
    }

    // Step 3: Distance Vector algorithm (Bellman-Ford update via intermediate node k)
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // If route through node k is shorter, update distance and next-hop
                if (dist[i][k] < INF && dist[k][j] < INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Step 4: Display the final routing table for every router
    for (int i = 0; i < n; i++) {
        printf("\nRouting table for router %c\n", 'A' + i);
        printf("Destination\tNext Hop\tDistance\n");
        for (int j = 0; j < n; j++) {
            if (dist[i][j] >= INF)
                printf("%c\t\t-\t\tInfinite\n", 'A' + j);
            else
                printf("%c\t\t%c\t\t%d\n", 'A' + j, 'A' + next[i][j], dist[i][j]);
        }
    }

    return 0;
}

