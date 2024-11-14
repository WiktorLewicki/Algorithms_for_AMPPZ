#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
vector<int> kraw[N], drzewo[N], wsteczne[N];
bitset<N> odw;
int low[N], gleb[N], ojc[N];
void dfs(int x){
	odw[x] = true;
	for(auto v : kraw[x]){
		if(!odw[v]){
			ojc[v]=x;
			drzewo[x].pb(v);
			drzewo[v].pb(x);
			dfs(v);
		}
		else if(v!=ojc[x]){
			wsteczne[x].pb(v);
			wsteczne[v].pb(x);
		}
	}
}
void dwuspojne(int x){
	odw[x] = true;
	low[x]=gleb[x];
	for(auto v : drzewo[x]){
		if(!odw[v]){
			gleb[v]=gleb[x]+1;
			dwuspojne(v);
			low[x]=min(low[x], low[v]);
		}
	}
	for(auto v : wsteczne[x]){
		low[x] = min(low[x], gleb[v]);
	}
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
		kraw[b].pb(a);
	}
	dfs(1);
	odw.reset();
	dwuspojne(1);
	return 0;
}
