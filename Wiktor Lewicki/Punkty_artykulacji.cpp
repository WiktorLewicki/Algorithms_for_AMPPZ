#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 2e4 + 5;
vector<int> graf[N];
vector<int> kraw[N][2];
int gleb[N], low[N];
bitset<N> odw;
void create(int x){
    odw[x]=true;
    for(auto v : graf[x]){
        if(odw[v]){
            kraw[v][1].pb(x);
        }
        else{
            kraw[x][0].pb(v);
            gleb[v]=gleb[x]+1;
            create(v);
        }
    }
}
void dfs(int x, vector<int> &ans, int st){
    odw[x]=true;
    low[x]=gleb[x];
    for(auto v : kraw[x][0]){
        if(!odw[v]) dfs(v, ans, st);
        low[x]=min(low[x], low[v]);
    }
    for(auto v : kraw[x][1]){
        low[x]=min(low[x], gleb[v]);
    }
    if(x==st) return;
    for(auto v : kraw[x][0]){
        if(low[v]>=gleb[x]){
            ans.pb(x);
            break;
        }
    }
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    int n, m;
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin>>a>>b;
        graf[a].pb(b);
        graf[b].pb(a);
    }
    for(int i=1;i<=n;i++){
		if(!odw[i]) create(i);
	}
    odw.reset();
    vector<int> ans;
    for(int i=1;i<=n;i++){
		if(odw[i]) continue;
		if((int)kraw[i][0].size()>1) ans.pb(i);
		dfs(i, ans, i);
	}
    sort(ans.begin(), ans.end());
    cout<<(int)ans.size()<<"\n";
    for(auto v : ans) cout<<v<<" ";
    return 0;
}
