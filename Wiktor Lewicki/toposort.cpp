#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
vector<int> kraw[N];
stack<int> toposort;
bitset<N> odw;
int t;
void dfs(int x, bool ok){
	odw[x]=true;
	for(auto v : kraw[x]){
		if(!odw[v]) dfs(v, ok);
	}
	toposort.push(x);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a, b;
		cin>>a>>b;
		kraw[a].pb(b);
	}
	for(int i=1;i<=n;i++){
		if(!odw[i]) dfs(i, 0);
	}
	return 0;
}
