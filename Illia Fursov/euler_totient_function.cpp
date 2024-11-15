// Euler's / totient function
// (counts the number of coprime numbers x, 1 <= x < n, for some n)
// O(sqrt(N))

// testing: https://www.dcode.fr/euler-totient

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll totient(ll n) {
	ll ans = n;
	for (int d = 2; d * 1ll * d <= n; d++) {
		if (n % d)
			continue;
		while (n % d == 0)
			n /= d;
		ans /= d, ans *= d - 1; 
	}
	if (n != 1)
		ans /= n, ans *= n - 1;
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ll n;
	cin >> n;
	cout << totient(n) << '\n';
}