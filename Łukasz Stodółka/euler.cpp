#include <bits/stdc++.h>
using namespace std;

void findEulerCycle(int start, unordered_map<int, vector<int>>& graph, vector<int>& cycle) {
    stack<int> stack;
    stack.push(start);

    while (!stack.empty()) {
        int current = stack.top();

        if (!graph[current].empty()) {
            int neighbor = graph[current].back();
            graph[current].pop_back();
            graph[neighbor].erase(find(graph[neighbor].begin(), graph[neighbor].end(), current));
            stack.push(neighbor);
        } else {
            cycle.push_back(current);
            stack.pop();
        }
    }
}

bool isEulerian(const unordered_map<int, vector<int>>& graph) {
    int startNodes = 0;
    for (const auto& [node, neighbors] : graph) {
        if (neighbors.size() % 2 != 0) return false;
        if (!neighbors.empty()) startNodes++;
    }
    return startNodes > 0;
}

int main() {
    int n, m;
    cin >> n >> m;

    unordered_map<int, vector<int>> graph;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    if (!isEulerian(graph)) {
        cout << "The graph is not Eulerian." << endl;
        return 0;
    }

    vector<int> cycle;
    findEulerCycle(graph.begin()->first, graph, cycle);

    cout << "Euler Cycle:" << endl;
    for (int node : cycle) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}

