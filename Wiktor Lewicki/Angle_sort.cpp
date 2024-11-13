#include <bits/stdc++.h>
#define pb push_back
typedef long double dl;
using namespace std;
const int N = 1e5 + 5;
pair<int, int> in[N];
pair<dl, int> kl[N*2];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int a, b;
		cin>>a>>b; //(a, b) is a point on the plane
		in[i]={a, b};
		dl pm=atan2(b, a)*(dl)180/M_PI;
		if(pm<0) pm+=360.0;
		kl[i]={pm, i};
	}
	sort(kl+1, kl+n+1);
	for(int i=1;i<=n;i++){
		cout<<kl[i].second<<"\n";
	}
	return 0;
}