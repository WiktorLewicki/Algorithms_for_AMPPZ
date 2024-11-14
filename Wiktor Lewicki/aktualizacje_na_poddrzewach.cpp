#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 5;
int d[N*4], push[N*4];
void add(int x, int val){
	d[x]+=val;
	push[x]+=val;
}
void pushuj(int x){
	add(x*2, push[x]);
	add(x*2+1, push[x]);
	push[x]=0;
}
void update(int x, int l, int r, int a, int b, int val){
	if(a<=l&&r<=b){
		add(x, val);
		return;
	}
	pushuj(x);
	int sr=(l+r)/2;
	if(a<=sr){
		update(x*2, l, sr, a, b, val);
	}
	if(sr<b){
		update(x*2+1, sr+1, r, a, b, val);
	}
	d[x]=d[x*2]+d[x*2+1];
}
int query(int x, int l, int r, int idx){
	if(l==r){
		return d[x];
	}
	pushuj(x);
	int sr=(l+r)/2, res=0;
	if(idx<=sr){
		res=query(x*2, l, sr, idx);
	}
	else{
		res=query(x*2+1, sr+1, r, idx);
	}
	d[x]=d[x*2]+d[x*2+1];
	return res;
	
}
