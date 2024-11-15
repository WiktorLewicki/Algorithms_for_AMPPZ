// Generator for trees

#include <bits/stdc++.h>

using namespace std;

// bounds for n;
// segment of the array of the existing vertices which we connect the next vertex to,
// sorted by their depths (% * (2^11))

// 1 <= ln <= rn <= 10^6
// 0 <= lc <= rc <= 2^11

const int N = 1e6 + 12;
const int M = 1 << 11;
const int B = 11;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r) {
	int d = r - l + 1;
	return (rng() % d) + l;
}

int n;
// set <pair <int, int>> used;
pair <int, int> e[N];
vector <int> by_dep[N];

void rand_shuffle() {
	if (n == 1)
		return;
	for (int rep = 0; rep < n * 2; rep++) {
		int i = get_rand(0, n - 2);
		int j = get_rand(0, n - 2);
		swap(e[i], e[j]);
	}
}

int st[N << 2];

void st_clear(int v, int tl, int tr) {
	st[v] = 0;
	if (tl == tr)
		return;
	int tm = (tl + tr) >> 1;
	st_clear(v << 1, tl, tm);
	st_clear((v << 1) ^ 1, tm + 1, tr);
}

void inc(int ind, int val, int v, int tl, int tr) {
	st[v] += val;
	if (tl == tr)
		return;
	int tm = (tl + tr) >> 1;
	if (ind <= tm)
		inc(ind, val, v << 1, tl, tm);
	else
		inc(ind, val, (v << 1) ^ 1, tm + 1, tr);
}

void inc(int ind, int val) {
	inc(ind, val, 1, 0, n - 1);
}

int get_kth(int k, int v, int tl, int tr) {
	// cerr << '\t' << k << ' ' << tl << ' ' << tr << '\n';
	if (tl == tr) {
		// assert(k == 0);
		return tl;
	}
	int tm = (tl + tr) >> 1;
	if (k < st[v << 1])
		return get_kth(k, v << 1, tl, tm);
	return get_kth(k - st[v << 1], (v << 1) ^ 1, tm + 1, tr);
}

int get_kth(int k) {
	return get_kth(k, 1, 0, n - 1);
}

int get(int l, int r, int v, int tl, int tr) {
	if (tl > tr)
		return 0;
	if (tl == tr) {
		assert(l <= tl and tr <= r);
		return st[v];
	}
	int tm = (tl + tr) >> 1;
	int ans = 0;
	if (l <= tm)
		ans += get(l, r, v << 1, tl, tm);
	if (r > tm)
		ans += get(l, r, (v << 1) ^ 1, tm + 1, tr);
	return ans;
} 

int get(int l, int r) {
	return get(l, r, 1, 0, n - 1);
}

void one(int ln, int rn, int lc, int rc) {
	// cerr << ln << ' ' << rn << ' ' << lc << ' ' << rc << '\n';
	assert(1 <= ln and ln <= rn and rn <= N);
	assert(0 <= lc and lc <= rc and rc <= M);
	n = get_rand(ln, rn);
	cout << n << '\n';
	for (int i = 1; i <= n; i++)
		by_dep[i].clear();
	st_clear(1, 0, n - 1);
	// used.clear();
	// used.insert({0, 0});
	by_dep[0].push_back(0);
	inc(0, 1);
	for (int v = 1; v < n; v++) {
		int li = (v * lc) >> B;
		int ri = (v * rc) >> B;
		li = min(li, v - 1);
		ri = min(ri, v - 1);
		assert(0 <= li and li <= ri and ri < v);

		int ui = get_rand(li, ri);
		int d = get_kth(ui);
		int sz = by_dep[d].size();
		assert(sz > 0);
		int u = by_dep[d][get_rand(0, sz - 1)];
		// auto [d, u] = *next(used.begin(), ui);
		// cerr << d << ' ' << u << '\n';

		inc(d + 1, 1);
		by_dep[d + 1].push_back(v);
		// used.insert({d + 1, v});

		e[v - 1] = {v, u};
		if (get_rand(0, 1))
			swap(e[v - 1].first, e[v - 1].second);
	}

	rand_shuffle();

	for (int i = 0; i < n - 1; i++) {
		auto [v, u] = e[i];
		cout << v + 1 << ' ' << u + 1 << '\n';
	}

	// cerr << (*used.rbegin()).first << '\n';
	int max_d = 0;
	while (by_dep[max_d + 1].size())
		max_d++;
	cerr << max_d << '\n';

	cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tt;
    cin >> tt;
    int step = (M - (1 << 10)) / tt;
    for (int i = 0; i < tt; i++) {
    	// cerr << tt << '\n';
    	int ln = 100'000, rn = 100'000;
    	int lc = (1 << 10) + step * i;
    	int rc = (1 << 10) + step * (i + 1);
    	one(ln, rn, lc, rc);
    }
}
