// Minimum Spanning Tree - priority_queue (Prim's) version

// testing: https://judge.yosupo.jp/problem/minimum_spanning_tree
// https://judge.yosupo.jp/submission/249578
// 327 ms, 47.88 Mib

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e5 + 12;

int n, m;
vector <int> g[N];
pair <int, pair <int, int>> e[N];
int pe[N];

bool used[N];

int out_sz;
int out[N];
ll sum;

bool cmp(int i, int j) {return e[i].first < e[j].first;}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for (int i = 0, a, b, w; i < m; i++) {
		cin >> a >> b >> w;
		g[a].push_back(i);
		g[b].push_back(i);
		e[i] = {w, {a, b}};
	}

	fill_n(used, n, false);

	priority_queue <pair <int, pair <int, int>>, vector <pair <int, pair <int, int>>>, greater <pair <int, pair <int, int>>>> pq;
	pq.push({0, {0, -1}});

	while (!pq.empty()) {
		auto [cost, go] = pq.top();
		auto [v, ei] = go;
		pq.pop();

		if (used[v])
			continue;
		used[v] = true;

		sum += cost;
		if (ei != -1)
			out[out_sz++] = ei;

		for (auto &ei : g[v]) {
			int u = e[ei].second.first ^ e[ei].second.second ^ v;
			if (used[u])
				continue;
			int w = e[ei].first;
			pq.push({w, {u, ei}});
		}
	}

	assert(out_sz == n - 1);
	cout << sum << '\n';
	for (int i = 0; i < out_sz; i++)
		cout << out[i] << ' ';
	cout << '\n';
}