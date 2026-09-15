#include <iostream>
using namespace std;

#define INF 999

int main()
{
    int n, cost[10][10], dist[10], visited[10] = {0};
    int i, j, count, min, next, source;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter cost matrix:\n";
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin >> cost[i][j];

    cout << "Enter source node: ";
    cin >> source;

    for(i=0;i<n;i++)
        dist[i] = cost[source][i];

    visited[source] = 1;

    for(count=1; count<n; count++)
    {
        min = INF;

        for(i=0;i<n;i++)
            if(!visited[i] && dist[i]<min)
            {
                min = dist[i];
                next = i;
            }

        visited[next] = 1;

        for(i=0;i<n;i++)
            if(!visited[i] &&
               dist[i] > dist[next] + cost[next][i])
                dist[i] = dist[next] + cost[next][i];
    }

    cout << "\nShortest distances:\n";
    for(i=0;i<n;i++)
        cout << source << " -> " << i << " = " << dist[i] << endl;

    return 0;
}