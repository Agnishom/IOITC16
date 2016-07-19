// Input : N, then N-1 edges. 1<=N<=1e5
//karanaggarwal
#include<bits/stdc++.h>
using namespace std;

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

#define si(x) scanf("%d",&x)
#define sll(x) scanf("%lld",&x)
#define pi(x) printf("%d\n",x)
#define F first
#define S second
#define PB push_back
#define MP make_pair

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;

const int MN = 500000;
const int LG = 23;

int P[LG][MN]; // for LCA of given tree. P[level][node] = 2**level parent of node.
int D[MN]; // Depth of node in a given tree.
VI T[MN]; // Given T.. only children.
VI G[MN]; // Given Graph.
int L[MN]; // Level of each node in BFS tree of graph.
VI bfs_parent[MN]; // BFS possible parents of each node in the given graph.
set<int> DG[MN]; // DAG that I am making.



void check(int x, int l, int h)
{
    assert(l<=h); assert(x>=l); assert(x<=h);
}
void dfs(int x,int d)
{
    D[x] = d;
    for(auto y : T[x])
        dfs(y,d+1);
}

PII lca(int x, int y)
{
    assert(x!=y);
    assert(D[x]==D[y]);
    /*
    if(D[x] < D[y])swap(x,y);
    int d = D[x] - D[y];int l =0; 
    while(d>0)
    {
        if(d&1) x = P[l][x]; 
        d/=2; l++;
    }
    if(x==y)return x;
    */
    for(int l = LG-1; l>=0; l--){
        if(P[l][x] == P[l][y])continue;
        x = P[l][x]; y = P[l][y];
    }
    return {x,y};
}
void bfs()
{
    L[0] = 0; 
    queue<int> Q; Q.push(0);
    bfs_parent[0].PB(0);
    while(!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        for(auto y : G[x])
        {
            if(L[y]==-1)
            {
                L[y] = 1 + L[x]; 
                Q.push(y);
            }
            if(L[y]<=L[x])continue;
            bfs_parent[y].PB(x);
        }
    }
}
void reset(int N)
{
    for(int i =0; i<N; i++)
    {
        T[i].clear();
        G[i].clear();
        bfs_parent[i].clear();
        DG[i].clear();
        L[i] = -1;
    }
}



bool check_DAG(int N)
{
    vector<int> IN(N);
    for(int i =0; i<N; i++)
        for(auto j : DG[i])
            IN[j]++;
    queue<int> Q;
    for(int i =0; i<N; i++)
        if(IN[i]==0) Q.push(i);
    int cnt =0;
    while(!Q.empty())
    {
        int x = Q.front(); Q.pop();
        cnt++; 
        for(auto y : DG[x]){
            IN[y]--; if(IN[y]==0)Q.push(y);
        }
    }
    return cnt == N;
}

int main()
{
    // some base stuff.
    memset(L,-1,sizeof(L));
    int N,M;
    while(cin>>N>>M)
    {
        trace(N,M);
//        check(N,1,MN);
        // scan graph. 1 based indexing.
        while(M--)
        {
            int x,y; 
            si(x); si(y); x--; y--;
            G[x].PB(y); G[y].PB(x);
        }
        // scan bfs tree. just n-1 parents.
        P[0][0] = 0;
        for(int i =1; i<N; i++)
        {
            si(P[0][i]); P[0][i]--;
            T[P[0][i]].PB(i);
        }
//        trace(N,M,"scanning done");
        // do dfs on bfs tree.. set depth.. 
        dfs(0,0);
//        trace("depth of tree nodes is set");
        // prepare for LCA
        for(int l = 1; l<LG; l++)
            for(int i =0; i<N; i++)
                P[l][i] = P[l-1][P[l-1][i]];
//        trace("lca precomp is done");
        bfs();
//        trace("bfs on graph is done");
        for(int i =1; i<N; i++)
        {
            int pt = P[0][i]; 
            for(auto y : bfs_parent[i])
                if(y != pt)
                {
                    PII tt = lca(pt,y);
                    DG[tt.F].insert(tt.S);
                }
        }
        bool valid = check_DAG(N);
        if(valid) cout<<"YES\n"; else cout<<"NO\n";
        reset(N);
    }
    return 0;	
}
