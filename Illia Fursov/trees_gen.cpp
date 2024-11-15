// Generator for trees

// to jest pierwsza wersja, i ona jest bardzo wolna (może, przez next)

#include <bits/stdc++.h>

using namespace std;

// bounds for n;
// segment of the array of the existing vertices which we connect the next vertex to,
// sorted by their depths (% * (2^10))

// 1 <= ln <= rn <= 10^6
// 0 <= lc <= rc <= 2^10

const int N = 1e5 + 12;
const int M = 1 << 10;
const int B = 10;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r) {
	int d = r - l + 1;
	return (rng() % d) + l;
}

int n;
set <pair <int, int>> used;
pair <int, int> e[N];

void rand_shuffle() {
	if (n == 1)
		return;
	for (int rep = 0; rep < n * 2; rep++) {
		int i = get_rand(0, n - 2);
		int j = get_rand(0, n - 2);
		swap(e[i], e[j]);
	}
}

void one(int ln, int rn, int lc, int rc) {
	// cerr << ln << ' ' << rn << ' ' << lc << ' ' << rc << '\n';
	assert(1 <= ln and ln <= rn and rn <= N);
	assert(0 <= lc and lc <= rc and rc <= M);
	n = get_rand(ln, rn);
	cout << n << '\n';
	used.clear();
	used.insert({0, 0});
	for (int v = 1; v < n; v++) {
		int li = (v * lc) >> B;
		int ri = (v * rc) >> B;
		li = min(li, v - 1);
		ri = min(ri, v - 1);
		assert(0 <= li and li <= ri and ri < n);

		int ui = get_rand(li, ri);
		// cerr << lc << ' ' << rc << ' ' << v << ' ' << li << ' ' << ri << ' ' << ui << '\n';
		// for (auto &[d, x] : used)
		// 	cerr << "{" << d << ' ' << x << "}" << ' ';
		// cerr << '\n';
		auto [d, u] = *next(used.begin(), ui);
		// cerr << d << ' ' << u << '\n';

		used.insert({d + 1, v});

		e[v - 1] = {v, u};
		if (get_rand(0, 1))
			swap(e[v - 1].first, e[v - 1].second);
	}

	rand_shuffle();

	for (int i = 0; i < n - 1; i++) {
		auto [v, u] = e[i];
		cout << v + 1 << ' ' << u + 1 << '\n';
	}

	cerr << (*used.rbegin()).first << '\n';
	// for (auto &[d, x] : used)
	// 	cerr << "{" << d << ' ' << x << "}" << ' ';
	// cerr << '\n';

	cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tt;
    cin >> tt;
    int step = (M - (1 << 9)) / tt;
    for (int i = 0; i < tt; i++) {
    	// cerr << tt << '\n';
    	int ln = 100'000, rn = 100'000;
    	int lc = (1 << 9) + step * i;
    	int rc = (1 << 9) + step * (i + 1);
    	one(ln, rn, 1020, 1020);
    }
}