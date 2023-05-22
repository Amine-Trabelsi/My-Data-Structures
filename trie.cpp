// trie solution for: https://cses.fi/problemset/list/
#include "bits/stdc++.h"
using namespace std;
// Hi ☻
const int mod = 1e9+7;
const int alph = 26;
const int M = 5002;
struct trie_node{
    bool is_end;
    int next[alph];
    trie_node(){ fill(next,next+alph,-1);}
};
vector<trie_node> trie(1);
void sinsert(string x){
    int v = 0;
    for(char c: x){
        int cc = c-'a';
        if(trie[v].next[cc] == -1){
            trie[v].next[cc] = trie.size();
            trie.emplace_back(); // default constructor
        }
        v = trie[v].next[cc];
    }
    trie[v].is_end = 1;
}

/*
bool sfind(string x){
    int v = 0;
    for(char c: x){
        int cc = c-'a';
        if(trie[v].next[cc] == -1)return false;
        v = trie[v].next[cc];
    }
    return trie[v].is_end;
}
*/

int dp[M];

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    string s;
    cin>>s;
    int k;
    cin>>k;
    for(int i=0;i<k;i++){
        string t;
        cin>>t;
        sinsert(t);
    }
    int n = s.size();
    dp[0] = 1;
    for(int i=0;i<n;i++){
        // add a letter while exists a word
        int v = 0;
        for(int j = i;j<n;j++){
            int cc = s[j]-'a';
            if(trie[v].next[cc] == -1)break;
            v = trie[v].next[cc];
            if(trie[v].is_end)dp[j+1] = (dp[j+1]+dp[i])%mod;
        }
    }

    cout<<dp[n]<<'\n';
    return 0;
}