#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int p[N];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin>>s;
	int n=s.size();
	s='.'+s;
	for(int i=2;i<=n;i++){
		int pref = p[i-1];
		while(pref && s[pref + 1] != s[i]){
			pref = p[pref];
		}
		if(s[pref + 1] == s[i]){
			pref++;
		}
		p[i] = pref;
	}
	for(int i=1;i<=n;i++){
		cout<<p[i]<<" ";
	}
	return 0;
}