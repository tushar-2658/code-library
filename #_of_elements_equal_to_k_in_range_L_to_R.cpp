/*
  call root[0] = new node(nullptr, nullptr, 0); build(root[0], 1, n) for allocating spaces
  before starting to use
  for updates(root[i - 1], root[i], 1, n, idx) where idx is a[idx]
  for queries -> query(root[L - 1], root[R], 1, n, k);
*/
#include "bits/stdc++.h"
using namespace std;

const int maxn = 100005;
using ll = long long;

struct node {
  node *left, *right;
  int val;
  node(){}
  node(node *l, node *r, int v){
    left = l;
    right = r;
    val = v;
  }
};

node *root[maxn];

void build(node *cur, int b, int e){
  if(b == e){
    cur -> val = 0;
    return;
  }
  int mid = (b + e) >> 1;
  cur -> left = new node(nullptr, nullptr, 0); 
  cur -> right = new node(nullptr, nullptr, 0);
  build(cur -> left, b, mid);
  build(cur -> right, mid + 1, e);
  cur -> val = cur -> left -> val + cur -> right -> val;
}

void upd(node *p, node *cur, int b, int e, int idx){
  if(idx < b or idx > e)return;
  if(b == idx && idx == e){
    cur -> val = p -> val + 1;
    return;
  }
  int mid = (b + e) >> 1;
  if(idx <= mid){
    if(cur -> left == nullptr)cur -> left = new node(nullptr, nullptr, 0);
    cur -> right = p -> right;
    upd(p -> left, cur -> left, b, mid, idx);
  }else {
    if(cur -> right == nullptr)cur -> right = new node(nullptr, nullptr, 0);
    cur -> left = p -> left; 
    upd(p -> right, cur -> right, mid + 1, e, idx);
  }
  cur -> val = cur -> left -> val + cur -> right -> val;
}

int query(node *p, node *cur, int b, int e, int idx){
  if(b == idx && e == idx){
    return cur -> val - p -> val;
  }else {
    int mid = (b + e) >> 1;
    if(idx <= mid){
      return query(p -> left, cur -> left, b, mid, idx);
    }else {
      return query(p -> right, cur -> right, mid + 1, e, idx);
    }
  }
}
