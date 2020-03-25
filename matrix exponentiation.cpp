/*  
  change sz before using
*/ 

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
ll mod = 1e9 + 7;

int sz = 10;

struct mat {
  ll m[sz][sz];
  mat(){
    for(int i = 0; i < sz; i++){
      for(int j = 0; j < sz; j++){
        m[i][j] = 0;
      }
    }
  }
};

mat indentity, base;

mat mult(const mat &p, const mat &q){
  mat ret;
  for(int i = 0; i < sz; i++){
    for(int j = 0; j < sz; j++){
      for(int k = 0; k < sz; k++){
        ret.m[i][j] = (ret.m[i][j] + (p.m[i][k] * q.m[k][j]) % mod) % mod;
      }
    }
  }
  return ret;
}

mat bigmod(const mat &p, ll q){
  if(q == 0)return indentity;
  if(q == 1)return p;
  if(q & 1){
    mat ret = bigmod(p, q - 1);
    return mult(ret, p);
  }else {
    mat ret = bigmod(p, q / 2);
    return mult(ret, ret);
  }
}

void init(){
  for(int i = 0; i < sz; i++){
    indentity.m[i][i] = 1;
  }
}
