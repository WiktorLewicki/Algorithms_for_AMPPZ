// Extended euclidean algorithm
// for some a, b (> 0?) finds such x, y that ax + by = gcd(a, b)
// testing: https://basecamp.eolymp.com/en/problems/5324

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return;
	}
	ll x1, y1;
	exgcd(b, a % b, x1, y1);
	// gcd(a, b) = b * x1 + (a % b) * y1 =
	// = b * x1 + (a - (a / b) * b) * y1 =
	// = b * x1 + a * y1 - (a / b) * b * y1 =
	// = a * y1 + b * (x1 - (a / b) * y1)
	x = y1;
	y = x1 - (a / b) * y1;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll a, b, x, y;
    cin >> a >> b;
    exgcd(a, b, x, y);
    if (gcd(a, b) != 1) {
    	cout << "NO" << '\n';
    	return 0;
    }
    cout << "YES" << '\n';
    cout << x << ' ' << y << '\n';
}