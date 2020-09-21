// virtual tree
// might be used when there is a tree and set of nodes given in queries to find some answer on that

#include "bits/stdc++.h"
using namespace std;

const int maxn = 100005;

vector<int> edges[maxn];
int n, q;

// LCA part start

int depth[maxn], sparse[maxn][20], par[maxn];
int st[maxn], ed[maxn], timer = 0;

void dfs(int x, int p){
  sparse[x][0] = p;
  depth[x] = depth[p] + 1;
  st[x] = ++timer;
  for(auto i : edges[x]){
    if(i != p){
      dfs(i, x);
    }
  }
  ed[x] = timer;
}

void build_lca(){
  for(int j = 1; j < 20; ++j){
    for(int i = 1; i <= n; ++i){
      if(sparse[i][j - 1] != -1){
        sparse[i][j] = sparse[sparse[i][j - 1]][j - 1];
      }
    }
  }
}

int LCA(int x, int y){
  if(depth[x] < depth[y])swap(x, y);
  for(int i = 19; i >= 0; --i){
    if(depth[x] - (1 << i) >= depth[y]){
      x = sparse[x][i];
    }
  }
  if(x == y)return x;
  for(int i = 19; i >= 0; --i){
    if(sparse[x][i] != sparse[y][i] && sparse[x][i] != -1 && sparse[y][i] != -1){
      x = sparse[x][i];
      y = sparse[y][i];
    }
  }
  return sparse[x][0];
}

// vitual tree part 

vector<int> g_VT[maxn]; // g_VT stores VT
int imp[maxn];

bool upper(int x, int y){
  return st[x] <= st[y] && ed[x] >= ed[y];
}

int build_VT(vector<int>& vert){
  sort(vert.begin(), vert.end(), [&](int x, int y){
    return st[x] < st[y];
  });
  int sz = vert.size();
  for(int i = 0; i + 1 < sz; ++i){
    vert.push_back(LCA(vert[i], vert[i + 1]));
  }
  sort(vert.begin(), vert.end(), [&](int x, int y){
    return st[x] < st[y];
  });
  vert.erase(unique(vert.begin(), vert.end()), vert.end());
  vector<int> sta;
  sta.push_back(vert[0]);
  for(int i = 1; i < (int)vert.size(); ++i){
    int u = vert[i];
    while(sta.size() >= 2 && !upper(sta.back(), u)){
      g_VT[sta.back()].push_back(sta[sta.size() - 2]);
      g_VT[sta[sta.size() - 2]].push_back(sta.back());
      sta.pop_back();
    }
    sta.push_back(u);
  }
  while(sta.size() >= 2){
    g_VT[sta[sta.size() - 2]].push_back(sta.back());
    g_VT[sta.back()].push_back(sta[sta.size() - 2]);
    sta.pop_back();
  }
  return sta.back();
}
