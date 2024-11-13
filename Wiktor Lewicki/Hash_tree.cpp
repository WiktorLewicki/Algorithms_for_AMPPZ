#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int st1 = 2137;
const int st2 = 2141;
const int MOD1 = 1e9 + 207;
const int MOD2 = 1e9 + 7;
const int N = 1e6 + 5;
pair<int, int> d[4*N], power[N], odd[N];
int rozm=1;
void update(int x, int l, int r, int idx, int val1, int val2){
	if(l==r){
		d[x]={val1, val2};
		return;
	}
	int sr=(l+r)/2;
	if(idx<=sr){
		update(x*2, l, sr, idx, val1, val2);
	}
	else{
		update(x*2+1, sr+1, r, idx, val1, val2);
	}
	d[x].first=((ll)d[x*2].first+d[x*2+1].first)%MOD1;
	d[x].second=((ll)d[x*2].second+d[x*2+1].second)%MOD2;
}
pair<int, int> query(int x, int l, int r, int a, int b){
	if(a<=l&&r<=b){
		return d[x];
	}
	pair<int, int> res={0, 0};
	int sr=(l+r)/2;
	if(a<=sr){
		pair<int, int> pom=query(x*2, l, sr, a, b);
		res.first=(res.first+pom.first)%MOD1;
		res.second=(res.second+pom.second)%MOD2;
	}
	if(sr<b){
		pair<int, int> pom=query(x*2+1, sr+1, r, a, b);
		res.first=(res.first+pom.first)%MOD1;
		res.second=(res.second+pom.second)%MOD2;
	}
	return res;
}
ll fast_pow(ll base, ll ww, int MOD){
	if(ww==0) return 1;
	if(ww&1){
		return (base*fast_pow(base, ww-1, MOD))%MOD;
	}
	else{
		ll res=fast_pow(base, ww/2, MOD);
		return (res*res)%MOD;
	}
}
pair<int, int> read(int a, int b){
	pair<int, int> ans=query(1, 1, rozm, a, b);
	ans.first=((ll)ans.first*odd[a-1].first)%MOD1;
	ans.second=((ll)ans.second*odd[a-1].second)%MOD2;
	return ans;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//O(n*logn+m*logm)
	int n;
	cin>>n;
	while(rozm<n){
		rozm*=2;
	}
	string s;
	cin>>s;
	s="."+s;
	s="";
	power[0]=odd[0]={1, 1};
	odd[1].first=fast_pow(st1, MOD1-2, MOD1);
	odd[1].second=fast_pow(st2, MOD2-2, MOD2);
	for(int i=1;i<=n;i++){
		power[i].first=((ll)power[i-1].first*st1)%MOD1;
		power[i].second=((ll)power[i-1].second*st2)%MOD2;
		if(i==1) continue;
		odd[i].first=((ll)odd[i-1].first*odd[1].first)%MOD1;
		odd[i].second=((ll)odd[i-1].second*odd[1].second)%MOD2;
	}
	for(int i=1;i<=n;i++){
		int upt1=((ll)power[i-1].first*s[i])%MOD1;
		int upt2=((ll)power[i-1].second*s[i])%MOD2;
		update(1, 1, rozm, i, upt1, upt2);
	}
	int q;
	cin>>q;
	while(q--){
		char z;
		cin>>z;
		if(z=='u'){
			int idx;
			char zm;
			cin>>idx>>zm;
			ll upt1=((ll)power[idx-1].first*zm)%MOD1;
			ll upt2=((ll)power[idx-1].second*zm)%MOD2;
			update(1, 1, rozm, idx, upt1, upt2);
			continue;
		}
		int a, b, c, d;
		cin>>a>>b>>c>>d;
		if(read(a, b)==read(c, d)) cout<<"1\n";
		else cout<<"0\n";
	}
	return 0;
}