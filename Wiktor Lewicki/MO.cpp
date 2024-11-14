#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define iii __int128_t
const int N = 2e5 + 5;
using namespace std;
int tab[N], kub[N*5], ans[N], sq;
set<int> cl;
bool cmp(array<int, 3> a, array<int, 3> b){
	if(a[0]/sq==b[0]/sq){
		return a[1] < b[1];
	}
	return a[0]/sq < b[0]/sq;
}
void solve(){
	int n, q;
	cin>>n>>q;
	sq=sqrt(n)+2;
	cl.clear();
	for(int i=1;i<=n;i++){
		cin>>tab[i];
		cl.insert(tab[i]);
	}
	vector<array<int, 3>> pm;
	for(int i=1;i<=q;i++){
		int a, b;
		cin>>a>>b;
		pm.pb({a, b, i});
	}
	sort(pm.begin(), pm.end(), cmp);
	int cnt=1, l=1, r=1;
	kub[tab[1]]++;
	for(auto &z : pm){
		pair<int, int> v={z[0], z[1]};
		while(l<v.first){
			if(kub[tab[l]]&1) cnt--;
			else cnt++;
			kub[tab[l]]--;
			l++;
		}
		while(l>v.first){
			l--;
			if(kub[tab[l]]&1) cnt--;
			else cnt++;
			kub[tab[l]]++;
		}
		while(r<v.second){
			r++;
			if(kub[tab[r]]&1) cnt--;
			else cnt++;
			kub[tab[r]]++;
		}
		while(r>v.second){
			if(kub[tab[r]]&1) cnt--;
			else cnt++;
			kub[tab[r]]--;
			r--;
		}
		ans[z[2]]=cnt;
	}
	for(int i=1;i<=q;i++){
		if(ans[i]) cout<<"NO\n";
		else cout<<"YES\n";
	}
	
	
	
	for(auto &v : cl){
		kub[v]=1e6;
	}
}