/* 
  BIT point update with range query in O(log(n))
*/
struct BIT{
  vector<int> bit;
  int n;
  void init(int sz, int val){
    bit.resize(sz + 1);
    n = sz;
    for(int i = 0; i <= sz; i++){
      bit[i] = val;
    }
  }
  void upd(int idx, int delta){
    for(; idx <= n; idx += (idx & -idx)){
      bit[idx] += delta;
    }
  }

  long long query(int idx){
    long long ret = 0;
    for(; idx > 0; idx -= (idx & -idx)){
      ret += bit[idx];
    }
    return ret;
  }
  long long query(int l, int r){
    return query(r) - query(l - 1);
  }
};
