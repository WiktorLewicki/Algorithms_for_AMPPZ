// Minimum Spanning Tree - DSU (Kruskal) version

// testing: https://judge.yosupo.jp/problem/minimum_spanning_tree
// https://judge.yosupo.jp/submission/248859
// 239 ms, 47.97 Mib

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e5 + 12;

int n, m;
vector <pair <int, int>> g[N];
pair <int, pair <int, int>> e[N];
int pe[N];

int dsu_pr[N], dsu_sz[N];

int out_sz;
int out[N];
ll sum;

bool cmp(int i, int j) {return e[i].first < e[j].first;}

void init_dsu(int n) {
	iota(dsu_pr, dsu_pr + n, 0);
	fill_n(dsu_sz, n, 1);
}

int get_root(int a) {return a == dsu_pr[a] ? a : dsu_pr[a] = get_root(dsu_pr[a]);}

bool merge(int a, int b) {
	a = get_root(a), b = get_root(b);
	if (a == b)
		return false;
	if (dsu_sz[a] < dsu_sz[b])
		swap(a, b);
	dsu_pr[b] = a;
	dsu_sz[a] += dsu_sz[b];
	return true;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for (int i = 0, a, b, w; i < m; i++) {
		cin >> a >> b >> w;
		g[a].push_back({b, w});
		g[b].push_back({a, w});
		e[i] = {w, {a, b}};
	}

	iota(pe, pe + m, 0);
	sort(pe, pe + m, cmp);
	init_dsu(n);
	out_sz = 0;
	sum = 0;
	for (int ei = 0; ei < m; ei++) {
		int i = pe[ei];
		if (merge(e[i].second.first, e[i].second.second)) {
			sum += e[i].first;
			out[out_sz++] = i;
		}
	}

	assert(out_sz == n - 1);
	cout << sum << '\n';
	for (int i = 0; i < out_sz; i++)
		cout << out[i] << ' ';
	cout << '\n';
}