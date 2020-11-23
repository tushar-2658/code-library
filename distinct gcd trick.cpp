/*
  a[i] stores the value of elements
  v[i] stores a pair where first element is the starting of changed gcd and second one is the new gcd
*/

#include "bits/stdc++.h"
using namespace std;

const int maxn = 500005;
using ll = long long;

int a[maxn];
vector<pair<int, int>> v[maxn];

int main(int argc, char const *argv[])
{
  int n, k;
  scanf("%d %d", &n, &k);
  for(int i = 1; i <= n; ++i){
    scanf("%d", &a[i]);
  }
  v[n].push_back({n, a[n]});
  for(int i = n - 1; i >= 1; --i){
    int cur = a[i];
    v[i].push_back({i, cur});
    for(auto j : v[i + 1]){
      int nw = __gcd(a[j.first], cur);
      if(nw != cur){
        cur = nw;
        v[i].push_back({j.first, cur});
      }
    }
  }
