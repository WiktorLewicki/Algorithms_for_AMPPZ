// Bellman-Ford algorithm
// Dijkstra for graphs with negative edges :)
// (directed graphs)

// testing: https://basecamp.eolymp.com/en/problems/1453

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e2 + 12;
const int M = 1e4 + 12;

int inf = 1e9 + 7;
int n, m;
int dst[N];
pair <int, pair <int, int>> e[M];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0, a, b, w; i < m; i++) {
    	cin >> a >> b >> w;
    	--a, --b;
    	e[i] = {w, {a, b}};
    }

    fill_n(dst, n, inf);
    dst[0] = 0;
    for (int rep = 1; rep <= n; rep++) {
    	bool was = false;
    	for (int i = 0; i < m; i++) {
    		int w = e[i].first;
    		auto [v, u] = e[i].second;
    		if (dst[v] < inf and dst[v] + w < dst[u]) {
    			was = true;
    			dst[u] = dst[v] + w;
    		}
    	}
    	if (!was)
    		break;
    	// assert(rep != n);
    }

    for (int i = 0; i < n; i++)
    	cout << (dst[i] < inf ? dst[i] : 30000) << ' ';
    cout << '\n';
}