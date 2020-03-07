/*
  bad() -> checks if intersection is to the left
  query() -> gives maximum value for x
  add() -> adds line to CHT
*/

#include "bits/stdc++.h"
using namespace std;

const int maxn = 1e5 + 5;
using ll = long long;

ll dp[maxn];
vector<ll> M, C;

bool bad(int l1, int l2, int l3){
	return (C[l3] - C[l1])*(M[l1] - M[l2]) < (C[l2] - C[l1])*(M[l1] - M[l3]);
}

void add(ll m, ll c){
	M.push_back(m);
	C.push_back(c);
	while(M.size() >= 3 && bad(M.size() - 3, M.size() - 2, M.size() - 1)){
		M.erase(M.end() - 2);
		C.erase(C.end() - 2);
	}
}

ll query(ll x, int b = 0, int e = M.size() - 1){
	if(b == e)return M[b] * x + C[b];
	if(e - b + 1 == 2){
		if(M[b] * x + C[b] > M[e] * x + C[e])return M[b] * x + C[b];
		return M[e] * x + C[e];
	}
	int mid = (b + e) >> 1; 
	if(mid > 0 && M[mid - 1] * x + C[mid - 1] > M[mid] * x + C[mid])return query(x, b, mid - 1); 
	else if(mid > 0 && M[mid] * x + C[mid] > M[mid - 1] * x + C[mid - 1])return query(x, mid, e);
	else return M[mid] * x + C[mid];
}
