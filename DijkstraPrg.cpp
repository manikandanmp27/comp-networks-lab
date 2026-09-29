#include <iostream>
using namespace std;

int main()
{
    int n, cost[10][10], dist[10], visited[10];
    int src, i, j, u, min;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter cost matrix:\n";
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin >> cost[i][j];

    cout << "Enter source: ";
    cin >> src;

    for(i=0;i<n;i++)
    {
        dist[i] = cost[src][i];
        visited[i] = 0;
    }

    dist[src] = 0;
    visited[src] = 1;

    for(i=1;i<n;i++)
    {
        min = 99;
        u = -1;

        for(j=0;j<n;j++)
            if(!visited[j] && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }

        visited[u] = 1;

        for(j=0;j<n;j++)
            if(!visited[j] && dist[u] + cost[u][j] < dist[j])
                dist[j] = dist[u] + cost[u][j];
    }

    cout << "\nShortest distances:\n";
    for(i=0;i<n;i++)
        cout << src << " -> " << i << " = " << dist[i] << endl;

    return 0;
}