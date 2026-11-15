#include <iostream>
using namespace std;

int main() {
    int n, src;
    int cost[10][10];          // cost adjacency matrix (99 = no direct link)
    int dist[10];              // dist[i]   = shortest distance from src to i
    int parent[10];            // parent[i] = node just before i on the shortest path
    int visited[10] = {0};     // visited[i] = 1 once i's shortest distance is final

    cout << "Enter number of vertices (6-10): ";
    cin >> n;

    if (n < 6 || n > 10) {
        cout << "Invalid number of vertices.\n";
        return 1;
    }
    cout << "Enter cost matrix (99 for no edge):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    cout << "Enter source: ";
    cin >> src;

    // STEP 1: start with the direct costs from the source
    for (int i = 0; i < n; i++) {
        dist[i] = cost[src][i];
        parent[i] = src;
    }
    visited[src] = 1;          // source is already final (distance 0)

    // STEP 2: repeat n-1 times
    for (int count = 1; count < n; count++) {

        // 2a: pick the unvisited node with the smallest distance
        int min = 99, u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }

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
        cout << "\nShortest path from " << src << " to " << v << ": ";
        if (dist[v] >= 99) {
            cout << "No path\n";
            continue;
        }
        int k = v;
        cout << k;
        while (k != src) {     // walk back using parent[]
            k = parent[k];
            cout << " <- " << k;
        }
        cout << "\nDistance = " << dist[v] << endl;
    }
    return 0;
}