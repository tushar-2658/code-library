// it basicallly keeps track of the heavy childs and erases the light childs 
// the sum of sizes of light chains for a subtree is atmost n / 2
// therefore, as we go down, the sizes of lightchains decreases by subtree size / 2
// total complexity O(n * logn)

#include "bits/stdc++.h"
using namespace std;

const int maxn = 100005;
vector<int> edges[maxn];
int sub[maxn], st[maxn], ed[maxn], timer = 0, vert[maxn];

void predfs(int x, int p){
  st[x] = ++timer; 
  vert[timer] = x;
  sub[x] = 1;
  for(auto i : edges[x]){
    if(i == p)continue;
    predfs(i, x);
    sub[x] += sub[i];
  }
  ed[x] = timer;
}

int ans[maxn];

void dfs(int x, int p, bool keep){
  int mx = -1, bigchild = -1;
  for(auto i : edges[x]){
    if(i == p)continue;
    if(sub[i] > mx){
      mx = sub[i];
      bigchild = i;
    }
  }
  for(auto i : edges[x]){
    if(i != p && i != bigchild){
      dfs(i, x, 0);
    }
  }
  if(bigchild != -1){
    dfs(bigchild, x, 1);
  }
  for(int i : edges[x]){
    if(i != p && i != bigchild){
      for(int j = st[i]; j <= ed[i]; ++j){
        // operation of some cnt[j]
      }
    }
  }
  // operation on cnt[x]
  // now cnt[i] contains my info for subtree of x
  if(keep == 0){
    for(int j = st[i]; j <= ed[i]; ++j){
      // clear cnt[j]
    }
  }
}

// call predfs to calculate subtree sizes and other infos
// then call dfs to answer subtree things
