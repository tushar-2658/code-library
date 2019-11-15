/* 
  par[i] -> stores the parent of i in centroid decomposition tree
 */

#include "bits/stdc++.h"
using namespace std;
 
const int maxn = 100005;
set<int> edges[maxn];
int sub[maxn], par[maxn];
 
void rem(int x, int y){
    edges[x].erase(y);
    edges[y].erase(x);
}
 
void dfs(int x, int p){
    sub[x] = 1;
    for(auto i : edges[x]){
        if(i == p)continue;
        dfs(i, x);
        sub[x] += sub[i];
    }
}
 
int find_centroid(int x, int p, int range){
    for(auto i : edges[x]){
        if(i == p)continue;
        if(sub[i] > range)return find_centroid(i, x, range);
    }return x;
}
 
void build(int x, int p){
    dfs(x, p);
    int c = find_centroid(x, 0, sub[x] / 2);
    par[c] = p;
    vector<int> v;
    copy(edges[c].begin(), edges[c].end(), back_inserter(v)); 
    for(auto i : v){
        rem(c, i);
        build(i, c);
    }
}
