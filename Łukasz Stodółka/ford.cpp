#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

// Number of vertices in the graph (adjust as needed)
const int MAX_NODES = 1000;

// Graph represented as an adjacency matrix
int capacity[MAX_NODES][MAX_NODES];

// Function to perform DFS and find an augmenting path
bool dfs(int s, int t, vector<int>& parent, int n, int visited[]) {
    visited[s] = true;
    if (s == t) return true;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && capacity[s][v] > 0) {
            parent[v] = s;
            if (dfs(v, t, parent, n, visited)) {
                return true;
            }
        }
    }
    return false;
}

// Ford-Fulkerson Algorithm
int fordFulkerson(int n, int s, int t) {
    int max_flow = 0;
    vector<int> parent(n);
    int visited[MAX_NODES];

    while (true) {
        memset(visited, 0, sizeof(visited));
        fill(parent.begin(), parent.end(), -1);

        // Find an augmenting path using DFS
        if (!dfs(s, t, parent, n, visited))
            break;

        // Find the bottleneck capacity
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, capacity[u][v]);
        }

        // Update capacities and reverse capacities along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;  // Add reverse edge
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int n, m;  // n: number of nodes, m: number of edges
    cin >> n >> m;

    memset(capacity, 0, sizeof(capacity));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        capacity[u][v] = w;  
    }

    int s, t; // Source and sink
    cin >> s >> t;

    int maxFlow = fordFulkerson(n, s, t);
    cout << "The maximum possible flow is " << maxFlow << endl;

    return 0;
}

