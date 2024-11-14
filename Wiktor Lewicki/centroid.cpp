#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
int sz[N];
vector<int> kraw[N], path[N];
bitset<N> odw;
void dfs1(int x, int ojc){
	sz[x]=1;
	for(auto v : kraw[x]){
		if(v!=ojc&&!odw[v]){
			dfs1(v, x);
			sz[x]+=sz[v];
		}
	}
}
void dfs2(int x, int ojc, int owner){
	path[x].pb(owner);
	for(auto v : kraw[x]){
		if(v!=ojc&&!odw[v]){
			dfs2(v, x, owner);
		}
	}
}
int szukaj(int x, int ojc, int tr){
	for(auto v : kraw[x]){
		if(v!=ojc&&!odw[v]&&sz[v]*2>tr){
			return szukaj(v, x, tr);
		}
	}
	return x;
}
void centroid(int x){
	dfs1(x, 0);
	int pom = szukaj(x, 0, sz[x]);
	dfs2(pom, 0, pom);
	odw[pom]=true;
	for(auto v : kraw[pom]){
		if(!odw[v]){
			centroid(v);
		}
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;;
	for(int i=1;i<=n-1;i++){
		int a, b;
		cin>>a>>b;
		kraw[a].pb(b);
		kraw[b].pb(a);
	}
	centroid(1);
	return 0;
}