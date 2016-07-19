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

#define TRACE

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
const int N = 510;
const int M = N*N;
namespace Dominator{
  VI g[N],tree[N],rg[N],bucket[N];
  int sdom[N],par[N],dom[N],dsu[N],label[N];
  int arr[N],rev[N],T;//1-Based directed graph input
  inline int Find(int u,int x=0){
    if(u==dsu[u])return x?-1:u;
    int v = Find(dsu[u],x+1);
    if(v<0)return u;
    if(sdom[label[dsu[u]]]<sdom[label[u]])
      label[u] = label[dsu[u]];
    dsu[u] = v;
    return x?v:label[u];
  }
  inline void Union(int u,int v){ //Add an edge u-->v
    dsu[v]=u; 	//yup,its correct :)
  }
  inline void dfs0(int u){
    T++;arr[u]=T;rev[T]=u;
    label[T]=T;sdom[T]=T;dsu[T]=T;
    for(int i=0;i<SZ(g[u]);i++){
      int w = g[u][i];
      if(!arr[w])dfs0(w),par[arr[w]]=arr[u];
      rg[arr[w]].PB(arr[u]);
    }
  }
  inline void dfs1(int u,int p,int P[]){
    P[u]=p;
    for(auto w:tree[u])
      if(w!=p)
        dfs1(w,u,P);
  }
  inline void reset(int n){
    for(int i=1;i<=n;i++){
      g[i].clear();rg[i].clear();tree[i].clear();arr[i]=0;
    }
    T=0;
  }
  void addEdge(int u,int v){
    g[u].PB(v);
  }
  //Build Dominator tree(in main)
  void get(int n,int root,int P[]){
    dfs0(root);assert(n==T);n=T;
    for(int i=n;i>=1;i--){
      for(int j=0;j<SZ(rg[i]);j++)
        sdom[i] = min(sdom[i],sdom[Find(rg[i][j])]);
      if(i>1)bucket[sdom[i]].PB(i);
      for(int j=0;j<SZ(bucket[i]);j++){
        int w = bucket[i][j],v = Find(w);
        if(sdom[v]==sdom[w])dom[w]=sdom[w];
        else dom[w] = v;
      }if(i>1)Union(par[i],i);
    }
    for(int i=2;i<=n;i++){
      if(dom[i]!=sdom[i])dom[i]=dom[dom[i]];
      tree[rev[i]].PB(rev[dom[i]]);
      tree[rev[dom[i]]].PB(rev[i]);
    }
    assert(root==rev[1]);
    dfs1(rev[1],rev[1],P);
  }//done :) 
}
int n,m,vis[N],P[N][N],par[N];
LL g[N][N],d[N];
bool central[N];
const LL INF = LL(1e16);
void dijkstra(int root){
  for(int i=0;i<=n;i++)d[i]=INF;
  Dominator::reset(n);SET(par,0);
  d[root]=0;SET(vis,0);SET(P,0);
  for(int i=1;i<=n;i++){
    int u = 0;
    for(int j=1;j<=n;j++)
      if(!vis[j] && d[j]<d[u])
        u = j;
    for(int w=1;w<=n;w++)
      if(g[u][w] && d[u] + g[u][w] < d[w]){
        d[w] = d[u] + g[u][w];
        SET(P[w],0);P[w][u]=1;
      }
      else if(g[u][w] && d[u]+g[u][w]==d[w])
        P[w][u]=1;
    vis[u]=1;
  }
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      if(P[i][j])
        Dominator::addEdge(j,i);
  Dominator::get(n,root,par);
  for(int i=1;i<=n;i++)
    if(par[i]!=root)
      central[par[i]]=true;
}
int main()
{
  si(n);si(m);
  for(int i=1;i<=m;i++){
    int u,v,w;
    si(u);si(v);si(w);
    g[u][v]=g[v][u]=w;
  }
  for(int i=1;i<=n;i++)
    dijkstra(i);
  int ans=0;
  for(int i=1;i<=n;i++)
    if(central[i])
      ans++;
  dout(ans);
  for(int i=1;i<=n;i++)
    if(central[i])
      printf("%d ",i);
  puts("");
  return 0;
}
