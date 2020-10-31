#include "bits/stdc++.h"
using namespace std;

const int maxn = 100005;
using ll = long long;

ll p_pow[2][maxn], inv[2][maxn];
ll p[2] = {29, 31};
ll mod[] = {(ll)(1e9 + 7), (ll)(1e9 + 9)};

ll bigmod(ll a, ll b, ll m){
  if(b == 0)return 1;
  if(b & 1){
    ll ret = bigmod(a, b - 1, m);
    return (ret * a) % m;
  }else {
    ll ret = bigmod(a, b >> 1, m);
    return (ret * ret) % m;
  }
}

void init(){
  p_pow[0][0] = 1;
  p_pow[1][0] = 1;
  inv[0][0] = bigmod(1, mod[0] - 2, mod[0]);
  inv[1][0] = bigmod(1, mod[1] - 2, mod[1]);
  for(int j = 0; j < 2; ++j){
    for(int i = 1; i < maxn; ++i){
      p_pow[j][i] = (p_pow[j][i - 1] * p[j]) % mod[j];
      inv[j][i] = bigmod(p_pow[j][i], mod[j] - 2, mod[j]);
    }
  }
}

struct Hash {
  vector<ll> H[2];
  void build(string& s){
    int sz = s.size();
    H[0].resize(sz);
    H[1].resize(sz);
    for(int j = 0; j < 2; ++j){
      for(int i = 0; i < sz; ++i){
        H[j][i] = ((s[i] - 'a' + 1) * p_pow[j][i]) % mod[j];
        if(i){
          H[j][i] = (H[j][i - 1] + H[j][i]) % mod[j];
        }
      }
    }
  }
  ll get_H(int id, int l, int r){
    if(l > r)return 0LL;
    if(l == 0)return H[id][r];
    ll ret = (((H[id][r] - H[id][l - 1] + mod[id]) % mod[id]) * inv[id][l]) % mod[id];
    return ret;
  }
  pair<ll, ll> get(int l, int r){
    return make_pair(get_H(0, l, r), get_H(1, l, r));
  }
};

Hash H, H1;
int n, m // n and m are sizes of two strings

int LCP(int l1, int l2){
  int lo = 1, hi = min(n - l1, m - l2), ans = 0;
  while(lo <= hi){
    int mid = (lo + hi) >> 1;
    if(H.get(l1, l1 + mid - 1) == H1.get(l2, l2 + mid - 1)){
      ans = mid;
      lo = mid + 1;
    }else {
      hi = mid - 1;
    }
  }
  return ans;
}
