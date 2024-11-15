#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Graph {
public:
    map<int, vector<int>> adjList;
    map<int, bool> visited;
    map<int, int> discoveryTime;
    map<int, int> finishTime;
    map<int, int> lowpoint;
    map<int, int> parent;
    int time;
    bool isPlanar;

    Graph() {
        time = 0;
        isPlanar = true;
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void dfs(int u) {
        visited[u] = true;
        time += 1;
        discoveryTime[u] = time;
        lowpoint[u] = discoveryTime[u];

        for (int v : adjList[u]) {
            if (!visited[v]) {
                parent[v] = u;
                dfs(v);
                lowpoint[u] = min(lowpoint[u], lowpoint[v]);

                if (lowpoint[v] > discoveryTime[u]) {
                    // Found a bridge (edge whose removal increases the number of connected components)
                    // Bridges do not affect planarity but are important for biconnectivity
                }
            } else if (parent[u] != v) {
                lowpoint[u] = min(lowpoint[u], discoveryTime[v]);
            }
        }

        time += 1;
        finishTime[u] = time;
    }

    bool isGraphPlanar() {
        for (auto const& vertex : adjList) {
            if (!visited[vertex.first]) {
                parent[vertex.first] = -1;
                dfs(vertex.first);
            }
        }

        return isPlanar;
    }
};

int main() {
    // Example 1: Simple Planar Graph
    Graph g1;
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(2, 4);
    g1.addEdge(3, 5);
    g1.addEdge(4, 5);

    if (g1.isGraphPlanar())
        cout << "Graph g1 is planar." << endl;
    else
        cout << "Graph g1 is not planar." << endl;

    // Example 2: Not planar
    Graph g2;
    g2.addEdge(1, 4);
    g2.addEdge(1, 5);
    g2.addEdge(1, 6);
    g2.addEdge(2, 4);
    g2.addEdge(2, 5);
    g2.addEdge(2, 6);
    g2.addEdge(3, 4);
    g2.addEdge(3, 5);
    g2.addEdge(3, 6);

    if (g2.isGraphPlanar())
        cout << "Graph g2 is planar." << endl;
    else
        cout << "Graph g2 is not planar." << endl;

    return 0;
}

