// Centroid (decomposition?) of a tree

// problem:  https://codeforces.com/contest/322/problem/E
// solution: https://codeforces.com/contest/322/submission/291513373

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 12;

int n;
vector <int> g[N];
int sz[N];
string out;

void dfs_sz(int v, int p) {
	sz[v] = 1;
	for (auto &x : g[v]) if (x != p and out[x] == '?')
		dfs_sz(x, v), sz[v] += sz[x];
}

void dfs_c(int v, char cur) {
	if (out[v] != '?')
		return;
	dfs_sz(v, -1);
	int r = v, pr = -1, big = -1;
	while (true) {
		big = -1;
		for (auto &x : g[r]) if (x != pr and out[x] == '?') {
			if (sz[x] > sz[v] / 2) {
				big = x;
				break;
			}
		}
		if (big == -1)
			break;
		pr = r, r = big;
	}
	v = r;
	out[v] = cur;
	for (auto &x : g[v]) if (out[x] == '?')
		dfs_c(x, cur + 1);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	out = string(n, '?');
	for (int i = 1, a, b; i < n; i++) {
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	dfs_c(0, 'A');
    
    for (int i = 0; i < n; i++)
        cout << out[i] << ' ';
    cout << '\n';
}