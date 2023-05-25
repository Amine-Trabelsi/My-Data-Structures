// solution to: https://cses.fi/problemset/result/1875234/
#include <bits/stdc++.h>
using namespace std;
const int M = 1005;
int tree[M][M];
int n;
void update(int x,int y,int val){
	for(int i=x;i<=n;i+= i & -i){
		for(int j=y;j<=n;j+= j & -j){
			tree[i][j] += val;
		}
	}
}
int query(int x,int y){
	int ans = 0;
	for(int i=x;i>0;i-= -i&i){
		for(int j=y;j>0;j -= -j&j){
			ans += tree[i][j];
		}
	}
	return ans;
}
int main(){
	int q;
	cin>>n>>q;
	vector<string> forest(n+1);
	for(int i=1;i<=n;i++){
		cin>>forest[i];
		for(int j=1;j<=n;j++){
			if(forest[i][j-1] == '*'){
				update(i,j,1);
			}
		}
	}
	while(q--){
		int t;
		cin>>t;
		if(t == 1){
			int x,y;
			cin>>x>>y;
			if(forest[x][y-1] == '*'){
				forest[x][y-1] = '.';
				update(x,y,-1);
			}else {
				update(x,y,1);
				forest[x][y-1] = '*';
			}
		}else{
			int a,b,c,d;
			cin>>a>>b>>c>>d;
			cout<< query(c,d)-query(c,b-1)-query(a-1,d)+query(a-1,b-1) << '\n';
		}
	}
	return 0;
}