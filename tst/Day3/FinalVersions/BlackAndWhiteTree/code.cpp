//Tanuj Khattar
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI > 	VVI;
typedef long long int 	LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

//#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);

const int N = int(2e5)+10;
const int SQRT = 500;
set<int> g[N];//edge list graph.graph is 1-based.
int A[N],P[N],root[N],level[N],BLOCK[N],ans[N];
int n,q;
void dfs(int u,int p){
  root[u]=root[p];//trace(u,level[u]);
  for(auto w:g[u])
    if(w!=p && BLOCK[w]==BLOCK[u]){
      level[w]=level[u]+1;ans[w]=ans[u]+A[w];
      dfs(w,u);
    }
}
void process(int t){
  //Build forest for each square root block
  int st = max(1,t*SQRT),en = min(n+1,(t+1)*SQRT);
  for(int i=st;i<en;i++)
    if(BLOCK[P[i]]!=t || P[i]==i)
      level[i]=0,root[i]=i,ans[i]=A[i],dfs(i,i);
  //done :)
}
int queryUp(int u,int p,int k){
  trace(u,p,k);
  int s = 0;//trace(u,p,k);
  while(root[u] != root[p]){
    s+=ans[u];//trace(s,u,k,ans[u]);
    if(s>=k){s-=ans[u];p = root[u];break;}
    u = P[root[u]];
  }
  k -= s;//trace(u,p,k);
  while(u > p){
    k-=A[u];
    if(!k)return u;
    u = P[u];
  }
  return u;
}
int lca(int a,int b){
//  trace(a,b,level[a],level[b]);
  if(level[a]>level[b])swap(a,b);
  while(level[b]>level[a])b = P[b];
  while(a!=b)a=P[a],b=P[b];
  return a;
}
int query(int a,int b,int k){
  int u = a, v = b;
  int su = 0, sv = 0;
  while(root[u]!=root[v]){
//    trace(u,v);
    if(v > u){sv += ans[v];v = P[root[v]];}
    else {su += ans[u]; u = P[root[u]];}
  }
//  trace(u,v,su,sv);
  int LCA = lca(u,v);
  su += ans[u] - ans[LCA] + A[LCA];
  sv += ans[v] - ans[LCA];
  if(su + sv < k)return -1;
  else if(su >= k)return queryUp(a,LCA,k);
  else return queryUp(b,LCA,sv - (k-su) + 1);
}
void update(int x){
  ans[x] = ans[x] - A[x];
  A[x] ^= 1;
  ans[x] = ans[x] + A[x];
  dfs(x,(BLOCK[P[x]]==BLOCK[x]?P[x]:x));
}
int main()
{
  si(n);si(q);
  //0:white 1:black
  for(int i=1;i<=n;i++)si(A[i]);
  for(int i=1;i<=n;i++)BLOCK[i]=i/SQRT;
  for(int i=2;i<=n;i++){
    si(P[i]);g[i].insert(P[i]);
    //trace(i,P[i]);
    g[P[i]].insert(i);
  }P[1]=1;
  //trace("ok");
  for(int i=0;i*SQRT<=n;i++)
    process(i);
  while(q--){
    char s[2];scanf("%s",s);
    //trace(s,q);
    if(s[0]=='T'){int x;si(x);update(x);}
    else if(s[0] == 'C'){
      int u,v;si(u);si(v);
      bool ok = true;ok &= (BLOCK[P[u]]!=BLOCK[u]);
      g[P[u]].erase(u);g[u].erase(P[u]);
      g[u].insert(v);g[v].insert(u);
      ok &= (BLOCK[v]!=BLOCK[u]);P[u]=v;
      if(ok)continue;
      if(BLOCK[P[u]]!=BLOCK[u]){ans[u]=A[u];root[u]=u;level[u]=0;dfs(u,u);}
      else {ans[u]=ans[P[u]]+A[u];level[u]=level[P[u]]+1;root[u]=root[P[u]];dfs(u,P[u]);}
    }
    else {
      int u,v,k;
      si(u);si(v);si(k);
      dout(query(u,v,k));
    }
  }
  return 0;
}
