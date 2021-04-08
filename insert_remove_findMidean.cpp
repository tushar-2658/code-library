struct DS {
  multiset<int> P, Q;
  ll sumP, sumQ; 
  DS(){
    sumP = sumQ = 0;
  }
  void add(int x){
    if(P.empty()){
      P.insert(x);
      sumP += x;
    }else if(*P.rbegin() < x){
      Q.insert(x); 
      sumQ += x;
    }else {
      P.insert(x); 
      sumP += x;
    }
    go();
  }
  void rem(int x){
    if(P.find(x) != P.end()){
      P.erase(P.find(x));
      sumP -= x;
    }else if(Q.find(x) != Q.end()){
      Q.erase(Q.find(x));
      sumQ -= x;
    }
    go();
  }
  void go(){
    if(P.size() < Q.size()){
      sumP += *Q.begin(); 
      sumQ -= *Q.begin(); 
      P.insert(*Q.begin());
      Q.erase(Q.begin());
    }
    if(P.size() > Q.size() + 1){
      sumP -= *P.rbegin(); 
      sumQ += *P.rbegin();
      Q.insert(*P.rbegin());
      P.erase(P.find(*P.rbegin()));
    }
  }
  ll get(){
    ll mid = *P.rbegin();
    ll ans = sumQ - sumP;
    ans -= mid * Q.size();
    ans += mid * P.size();
    return ans;
  }
};
