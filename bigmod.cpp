// returns pow(a, b) % mod
ll bigmod(ll a, ll b){
  ll ret = 1;
  while(b){
    if(b & 1)ret = (ret * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return ret;
}
