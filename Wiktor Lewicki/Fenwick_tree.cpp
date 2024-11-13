#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int d[N], n;
void update(int x, int w){
    if(x>n)return;
    d[x] = d[x] + w;
    update(x + (x & (-x)), w);
}
int sum(int x){
    if (!x) return 0;
    return d[x] + sum(x - (x & (-x)));
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		update(i, a);
	}
	cout<<sum(1)<<"\n";
	cout<<sum(3)<<"\n";
	cout<<sum(6)<<"\n";
	return 0;
}