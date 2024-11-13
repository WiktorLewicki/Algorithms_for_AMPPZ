#include <bits/stdc++.h>
#define pb push_back
typedef long long ll;
using namespace std;
vector<ll> fac;
ll fast_pow(ll base, ll w, ll mod){
	if(w==0) return 1;
	if(w&1){
		return (base*fast_pow(base, w-1, mod))%mod;
	}
	else{
		ll res=fast_pow(base, w/2, mod);
		return (res*res)%mod;
	}
}
bool checker(ll n, ll a){
	ll d=n-1;
	while((d&1)==0){
		d>>=1;
	}
	ll x = fast_pow(a, d, n);
	if(x==1||x==n-1) return true;
	while(d!=n-1){
		x=(x*x)%n;
		d<<=1;
		if(x==1) return false;
		if(x==n-1) return true;
	}
	return false;
}
bool rabin(ll n){
	if(n==2) return true;
	if(n%2==0||n<2) return false;
	for(auto v : fac){
		if(v>n-2) continue;
		if(checker(n, v)==false){
			return false;
		}
	}
	return true;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	fac.pb(2);
	fac.pb(3);
	fac.pb(5);
	fac.pb(7);
	fac.pb(11);
	fac.pb(13);
	fac.pb(17);
	fac.pb(19);
	fac.pb(23);
	fac.pb(29);
	fac.pb(31);
	fac.pb(37);
	ll n;
	cin>>n;
	if(rabin(n)) cout<<"Primary\n";
	else cout<<"Not primary\n";
	return 0;
}