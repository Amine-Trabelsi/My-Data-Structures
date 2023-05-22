// Solution to: https://cses.fi/problemset/task/1735/
#include "bits/stdc++.h"
using namespace std;
// Hi ☻
const int M = 2e5+5;
vector<int> a;
long long tree[M*5],chan[M*5],inc[M*5];
void build(int v,int l,int r){
    if(l == r){
        tree[v] = a[l];
        return ;
    }
    int mid = (l+r)/2;
    build(v*2,l,mid);
    build(v*2+1,mid+1,r);
    tree[v] = tree[v*2]+tree[v*2+1];
}
void update(int v,int tl,int tr,int t,int ql,int qr, long long val);
 
void push(int v,int tl,int tr){
    int mid= (tl+tr)/2;
    if(chan[v] != 0){
        update(v*2,tl,mid,2,tl,mid,chan[v]);
        update(v*2+1,mid+1,tr,2,mid+1,tr,chan[v]);
        chan[v] = 0;
    }else if(inc[v]){
        update(v*2,tl,mid,1,tl,mid,inc[v]);
        update(v*2+1,mid+1,tr,1,mid+1,tr,inc[v]);
        inc[v] = 0;
    }
}
void update(int v,int tl,int tr,int t,int ql,int qr, long long val){
    if(tl > qr || tr < ql)return;
    if(tl >= ql && tr <= qr){
        if(t == 1){
            tree[v] +=(tr-tl+1LL)*val;
            if(chan[v] == 0){
                inc[v] += val;
            }else chan[v] += val;
        }else{
            tree[v] = (tr-tl+1LL)*val;
            chan[v] = val;
            inc[v] = 0;
        }
        return;
    }
    push(v,tl,tr);
    int mid = (tl+tr)/2;
    update(v*2,tl,mid,t,ql,qr,val);
    update(v*2+1,mid+1,tr,t,ql,qr,val);
    tree[v] = tree[v*2]+tree[v*2+1];
}
long long que(int v,int tl,int tr,int ql,int qr){
    if(tl > qr || tr < ql)return 0;
    if(tl >= ql && tr <= qr)return tree[v];
    push(v,tl,tr);
    int mid= (tl+tr)/2;
    return que(v*2,tl,mid,ql,qr)+que(v*2+1,mid+1,tr,ql,qr);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,q;
    cin>>n>>q;
    a.assign(n,0);
    for(auto &i:a)cin>>i;
    build(1,0,n-1);
    while(q--){
        int t;
        cin>>t;
        if(t <3){
            int l,r,val;
            cin>>l>>r>>val;
            update(1,0,n-1,t,l-1,r-1,val);
        }else{
            int l,r;
            cin>>l>>r;
            cout << que(1,0,n-1,l-1,r-1) << '\n';
        }
    }
    return 0;
}