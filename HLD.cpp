/*  
  pos[] -> position of element in HLD chain
  retrive[] -> get back the real position from HLD chain
  heavy[] -> heavy edge
  update the segtree function as required
*/
#include "bits/stdc++.h"
using namespace std;

const int maxn = 100005;
vector<int> edges[maxn];
int heavy[maxn], par[maxn], depth[maxn], sub[maxn];

int dfs(int x, int p){
    int c_size = 1;
    int max_size = 0;
    par[x] = p;
    depth[x] = depth[p] + 1;
    for(auto i : edges[x]){
        if(i == p)continue;
        int sub_size = dfs(i, x);
        c_size += sub_size;
        if(sub_size > max_size){
            max_size = sub_size;
            heavy[x] = i;
        }
    }return c_size;
}

int head[maxn], pos[maxn], retrive[maxn];
int cnt = 0;

void decompose(int x, int p){
    head[x] = p;
    pos[x] = ++cnt;
    retrive[cnt] = x;
    if(heavy[x] != 0){
        decompose(heavy[x], p);
    }
    for(auto i : edges[x]){
        if(i != heavy[x] && i != par[x]){
            decompose(i, i);
        }
    }
}

int query(int a, int b){
    int res = 0;
    while(head[a] != head[b]){
        if(depth[head[a]] > depth[head[b]])swap(a, b);
        res = max(res, segtree(1, 1, n, pos[head[b]], pos[b]));
        b = par[head[b]];
    }
    if(depth[a] > depth[b])swap(a, b);
    res = max(res, segtree(1, 1, n, pos[a], pos[b]));
    return res;
}
