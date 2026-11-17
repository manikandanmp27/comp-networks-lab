#include <iostream>
using namespace std;

#define INF 99

int cost[10][10];      // cost adjacency matrix (99 = no direct link)
int dist[10];          // dist[i]   = shortest distance from src to i
int parent[10];        // parent[i] = node just before i on the shortest path
int visited[10];       // visited[i] = 1 once i's shortest distance is final

// Print the path forward recursively (e.g., 1 -> 4 -> 2)
void printPath(int v) {
    if (parent[v] != -1) {
        printPath(parent[v]);
        cout << " -> ";
    }
    cout << v;
}

int main() {
    int n, src;
    cout << "Enter number of vertices (6-10): ";
    cin >> n;

    cout << "Enter cost matrix (99 for no link):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    cout << "Enter source vertex: ";
    cin >> src;

    // STEP 1: start with the direct costs from the source
    for (int i = 0; i < n; i++) {
        dist[i] = cost[src][i];
        parent[i] = (cost[src][i] < INF && i != src) ? src : -1;
    }
    dist[src] = 0;
    visited[src] = 1;      // source is already final (distance 0)

    // STEP 2: repeat n-1 times
    for (int count = 1; count < n; count++) {

        // 2a: pick the unvisited node with the smallest distance
        int min = INF, u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && dist[j] < min)
                min = dist[u = j];

        if (u == -1) break;    // remaining nodes are unreachable
        visited[u] = 1;        // fix u's distance permanently

        // 2b: relax: see if going through u gives a shorter route
        for (int v = 0; v < n; v++)
            if (!visited[v] && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u; // remember the route goes through u
            }
    }

    // STEP 3: print path and distance for every node
    for (int v = 0; v < n; v++) {
        if (v == src) continue;
        cout << "\nShortest path from " << src << " to " << v << ":\n";
        if (dist[v] >= INF) {
            cout << "No path exists.\n";
        } else {
            printPath(v);
            cout << "\nDistance = " << dist[v] << "\n";
        }
    }

    return 0;
}
