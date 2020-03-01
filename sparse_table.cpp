/* 
  sparse table for max query in range
*/

int sparse[maxn][20]; 

void build(vector<int>& v){
  for(int i = 0; i < n; i++){
    sparse[i][0] = v[i];
  }
  for(int j = 1; j < 15; j++){
    for(int i = 0; i < n; i++){
      sparse[i][j] = max(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
    }
  }
}

int query(int id, int l, int r){
  int j = log2(r - l + 1);
  return max(sparse[l][j], sparse[r - (1 << j) + 1][j]);
}
