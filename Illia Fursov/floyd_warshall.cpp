// Floyd-Warshall algorithm
// the lengths of the shortest paths between every pair of vertices in the graph
// !!! negative weights are not allowed !!!

// testing: https://basecamp.eolymp.com/en/problems/974
// testing: https://basecamp.eolymp.com/en/problems/975

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 112;

int n;
int a[N][N];
int dp[N][N];

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
		cin >> a[i][j];

	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
		dp[i][j] = a[i][j];

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
                // trzeba pamietac o -1 / inf itd.
				if (dp[i][k] + dp[k][j] < dp[i][j])
					dp[i][j] = dp[i][k] + dp[k][j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << dp[i][j] << ' ';
		cout << '\n';
	}
}