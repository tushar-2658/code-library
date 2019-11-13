/*
  p_pow[] -> powers of p (prime)
  inv[] -> modular inverse of powers of p
  hashes[] -> hash of string
*/
#include "bits/stdc++.h"
using namespace std;

string s;
using ll = long long; 
const int maxn = 1000005;
ll p = 31;
ll mod = 1e9 + 7; 
ll hashes[maxn], p_pow[maxn];

ll bigmod(ll a, ll b){
    if(b == 0)return 1;
    if(b & 1){
        ll ret = bigmod(a, b - 1);
        return (a * ret) % mod;
    }else {
        ll ret = bigmod(a, b / 2);
        return (ret * ret) % mod;
    }
}

int n;
ll inv[maxn];

// computes hash for string s
void compute_hashes(){
    p_pow[0] = 1;
    inv[0] = bigmod(p_pow[0], mod - 2);
    for(int i = 1; i < n; i++){
        p_pow[i] = (p_pow[i - 1] * p) % mod;
        inv[i] = bigmod(p_pow[i], mod - 2);
    }
    for(int i = 0; i < n; i++){
        hashes[i] = ((s[i] - 'a' + 1) * p_pow[i]) % mod;
        if(i > 0){
            hashes[i] = (hashes[i] + hashes[i - 1]) % mod;
        }
    }
} 

// gives hash value for s[l...r]
ll get_hash(int l, int r){
    if(l > r)return 0LL;
    if(l == 0)return hashes[r];
    return (((hashes[r] - hashes[l - 1] + mod) % mod) * inv[l]) % mod;
}
