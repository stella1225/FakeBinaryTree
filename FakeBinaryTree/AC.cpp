#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MOD = 998244353;

//頂点vの高さと，右端からの距離求める
pair<int,int> pwd(int v){
  if(v==1) return {1,0};
  int mx=2e4, mini=0;
  while(mx-mini>1){
    int mid=(mx+mini)/2;
    int val=mid*(mid+1)/2;
    if(val<v) mini=mid;
    else mx=mid;
  }
  int diff=mx*(mx+1)/2-v;
  //cout<<"pwd "<<mx<<" "<<diff<<endl;
  return {mx, diff};
}

//移動する
void operation(deque<int> &q, map<int,ll> &mp, char type){
  int size=mp.size();
  set<int> st;
  //assert(q.size()==size);
  int M=200010000;
  
  while(size--){
    //初めにいたものがでてくるように前からとりだす
    int v=q.front(); q.pop_front();
    ll cnt=mp[v]; mp.erase(v);
    //vがどこにいるのか調べる
    auto [h,diff]=pwd(v);
    //移動先の頂点番号を求める
    //左の子へ移動
    if(type=='L'){
      int lc=(h+1)*(h+2)/2-diff-1;
      if(lc>M){
        cout<<-1<<endl;
        exit(0);
      }
      //後ろから追加する
      st.insert(lc);
      mp[lc]+=cnt;
      mp[lc]%=MOD;
    }
    //右の子へ移動
    if(type=='R'){
      int rc=(h+1)*(h+2)/2-diff;
      if(rc>M){
        cout<<-1<<endl;
        exit(0);
      }
      st.insert(rc);
      mp[rc]+=cnt;
      mp[rc]%=MOD;
    }
    //親へ移動
    if(type=='U'){
      //親がない場合
      if(v==1){
        cout<<"-1"<<endl;
        exit(0);
      }
      //vが右端（右親なし）か左端（左親なし）か判定
      int no_rp=0,no_lp=0;
      if(diff==0) no_rp=1;
      if(diff==h-1) no_lp=1;
      //移動先の頂点番号求める
      if(no_rp==0) {
        int rp=h*(h-1)/2-diff+1;
        st.insert(rp);
        mp[rp]+=cnt;
        mp[rp]%=MOD;
      }
      if(no_lp==0){
        int lp=h*(h-1)/2-diff; 
        st.insert(lp);
        mp[lp]+=cnt;
        mp[lp]%=MOD;
      }
    }
  }
  //setからqueueに移す
  for(auto&v:st){
    q.push_back(v);
  }
}


int main(){
  int N,V; cin>>N>>V;
  string S; cin>>S;

  //size,cnt
  map<int,ll> mp;
  mp[V]=1;

  //vertex
  deque<int> q;
  q.push_back(V);

  //探索
  for(int i=0; i<N; i++){
    operation(q, mp, S[i]);
  }
  
  //カウント
  ll ans=0;
  for(auto x:mp){
    auto [v, cnt]=x;
    ans+=cnt;
    ans%=MOD;
  }
  cout<<ans<<endl;
}