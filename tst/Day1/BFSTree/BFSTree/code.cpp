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
const int N = int(1e5)+10;
const int M = int(2e5)+10;
const int LOGN = 20;
int U[M],V[M],DP[LOGN][N],level[N],depth[N],vis[N],indeg[N],arr[N],dep[N],t;
VI g[N],P[N],dag[N];
bool ok = true;
int adj(int u,int e){
  return U[e]^V[e]^u;
}
void bfs(int root){
  SET(vis,0);queue<int> Q;
  Q.push(root);vis[root]=1;
  while(!Q.empty()){
    int u = Q.front();Q.pop();
    for(auto e:g[u]){
      int w = adj(u,e);
      if(vis[w] && depth[w]<depth[u])P[u].PB(w);
      else if(!vis[w])depth[w]=depth[u]+1,Q.push(w),vis[w]=1;
    }
  }
}
int go(int i){
  if(level[i]!=0)return level[i];
  if(i==DP[0][i])return level[i];
  return level[i] = 1 + go(DP[0][i]);
}
II lca(int a,int b){
  assert(level[a]==level[b]);
  for(int i=LOGN-1;i>=0;i--)
    if(DP[i][a]!=DP[i][b])
      a = DP[i][a],b=DP[i][b];
  return {a,b};
}
void dfs(int u){
  arr[u]=++t;//trace(u,arr[u],dep[u]);
  for(auto w:dag[u])
    if(!arr[w])dfs(w);
    else if(arr[w]<= arr[u] && !dep[w]) ok=false;
  dep[u]=++t;
}
int main()
{
  //first take the graph as input
  int n,m;
  int T;si(T);
  while(T--){
      ok=true;t=0;
    si(n);si(m);
    for(int i=1;i<=n;i++)g[i].clear(),dag[i].clear(),P[i].clear(),vis[i]=level[i]=depth[i]=indeg[i]=arr[i]=dep[i]=0;
    for(int i=1;i<=m;i++){
      scanf("%d %d",U+i,V+i);
      g[U[i]].PB(i);g[V[i]].PB(i);
    }
    for(int i=2;i<=n;i++)si(DP[0][i]);
    //then take the rooted tree as input. Root = 1
    DP[0][1]=1;bfs(1);
    //do the bfs from 1 and cross check the levels
    //process the tree
    for(int i=1;i<=n;i++)go(i);
    for(int i=1;i<LOGN;i++)
      for(int j=1;j<=n;j++)
        DP[i][j]=DP[i-1][DP[i-1][j]];
    //check
    for(int i=1;i<=n;i++)
      if(level[i]!=depth[i])
        ok=false;
    if(!ok){puts("NO");continue;}
    //build the dag
    for(int i=1;i<=n;i++)
      for(auto p:P[i])
        if(DP[0][i]!=p){
          II x = lca(DP[0][i],p);
          dag[x.F].PB(x.S);indeg[x.S]++;
        }
    for(int i=1;i<=n;i++){
      sort(ALL(dag[i]));
      dag[i].resize(distance(dag[i].begin(),unique(ALL(dag[i]))));
    }
    //check for a cycle in the dag
    for(int i=1;i<=n;i++)
      if(!arr[i])
        dfs(i);
    //done :)
    puts(ok?"YES":"NO");
  }
  return 0;
}
