// some modulos:

/*
1069946021
1223589629
1200006253
1974483727
1495465463
1723289423
1292779261
1813521821
1701238439
1885899101
1962009883
1662177443
1199158277
1517318987
1684372891
1455791437
1966566673
1706928529
1368673711
1666118477
1221703891
1133471681
1882726669
1482809467
1928526659
/*

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define int ll

bool prime(int n) {
	if (n < 2)
		return false;
	if (n % 2 == 0)
		return n == 2;
	for (int d = 3; d * 1ll * d <= n; d += 2) {
		if (n % d == 0)
			return false;
	}
	return true;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r) {
	int d = r - l + 1;
	return (rng() % d) + l;
}

int go(int l, int r) {
	int n = get_rand(l, r);
	for (int d = 1; d <= 1000; d++) {
		if (n - d >= 2 and prime(n - d))
			return n - d;
		if (prime(n + d))
			return n + d;
	}
	return -1;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tt = 25;
    for (int i = 1; i <= tt; i++) {
    	int l = 1'000'000'000;
    	int r = 2 * l;
    	int n = go(l, r);
    	assert(prime(n));
    	if (n != -1)
    		cout << n << '\n';
    }
}
