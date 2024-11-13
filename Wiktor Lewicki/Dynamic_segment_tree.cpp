#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;

struct node{
	int l=0;
	int r=0;
	ll sum=0;
};
vector<node> d;
int create(){
	d.emplace_back();
	return (int)d.size()-1;
}
void update(int x, int l, int r, int idx, int val){
	if(l==r){
		d[x].sum+=val;
		return;
	}
	int sr=(l+r)/2;
	if(idx<=sr){
		if(!d[x].l){
			d[x].l=create();
		}
		update(d[x].l, l, sr, idx, val);
	}
	else{
		if(!d[x].r){
			d[x].r=create();
		}
		update(d[x].r, sr+1, r, idx, val);
	}
	d[x].sum=d[d[x].l].sum+d[d[x].r].sum;
}
ll query(int x, int l, int r, int a, int b){
	if(a<=l&&r<=b){
		return d[x].sum;
	}
	ll res=0;
	int sr=(l+r)/2;
	if(a<=sr&&d[x].l){
		res+=query(d[x].l, l, sr, a, b);
	}
	if(sr<b&&d[x].r){
		res+=query(d[x].r, sr+1, r, a, b);
	}
	return res;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	d.resize(2);
	int q, rozm=(1<<30);
	cin>>q;
	while(q--){
		char z;
		cin>>z;
		if(z=='U'){
			int idx, val;
			cin>>idx>>val;
			update(1, 1, rozm, idx, val);
		}
		else{
			int a, b;
			cin>>a>>b;
			cout<<query(1, 1, rozm, a, b)<<"\n";
		}
	}
	return 0;
}