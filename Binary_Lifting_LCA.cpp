// Solution to problem: https://cses.fi/problemset/task/1688/
#include "bits/stdc++.h"
using namespace std;
// Hi
const int M = 2e5+5;
int tin[M+5],tout[M+5],depth[M+5];
vector<int> graph[M+5];
int lift[M+5][25]; // lift[i][j] = lift node i 2^j times
int timer = 0;
void dfs(int node, int par){
	tin[node]=timer++;
	lift[node][0] = par;
	for(int i=1;i<20;i++){
		lift[node][i] = lift[lift[node][i-1]][i-1];
	}
	for(auto i:graph[node]){
		if(i!=par){
			depth[i] = depth[node]+1;
			dfs(i,node);
		}
	}
	tout[node]=timer++;
}
bool isparent(int u,int v){
	return tin[u] <= tin[v] && tout[v] <= tout[u]; 
}
int lca(int u,int v){
	if(isparent(u,v))return u;
	if(isparent(v,u))return v;
	for(int i=19; i>=0; i--) if(!isparent(lift[u][i],v)) u=lift[u][i];
	return lift[u][0];
}
 
int lif(int u, int k){
	for(int i=0; i<20; i++) if((k)&((1)<<(i))) u=lift[u][i];
	return u;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,q,x;
	cin>>n>>q;
	for(int i=1;i<n;i++){
		cin>>x;x--;
		graph[i].push_back(x);
		graph[x].push_back(i);
	}
	dfs(0,0);
	while(q--){
		int a,b;
		cin>>a>>b;
		a--,b--;
		cout<<lca(a,b)+1<<'\n';
	}
    return 0;
}
