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

const int N = int(1e5)+10;
const int Q = int(1e5)+1;
const int SQRT = 400;
int BIT[SQRT][SQRT+10],qlen,BLOCK[N],dsu[N],MX[SQRT],MN[SQRT],pos[N],add[SQRT];
VI A[SQRT];
void update(int BIT[],int x,int add=1){
  for(;x<=SQRT;x+=(x^(x&(x-1))))
    BIT[x]+=add;
}
int get(int BIT[],int x){
  int ret = 0;
  for(;x;x=(x&(x-1)))ret+=BIT[x];
  return ret;
}
int f(int x){
  if(dsu[x]==x)return x;
  return dsu[x] = f(dsu[x]);
}
int main()
{
  int n,qq;
  si(n);si(qq);
  for(int i=1;i<=n;i++)BLOCK[i]=i/SQRT,pos[i]=i%SQRT;
  for(int i=0;i<=n;i++)A[BLOCK[i]].PB(0);
  for(int i=1;i<=n+1;i++)dsu[i]=i;
  int xx = 0;
  for(int q=1;q<=qq;q++)
  {
    int t,l,r;
    si(t);si(l);si(r);
   // trace(q,t);
    if(t==3 && q < Q){xx++;puts("YES");continue;}
    if(t==1){
      int x;si(x);
      if(!x)continue;
      int L = l,R = r;
     // trace(L,R);
      while((l = f(l))<=r){
     //   trace(l,r,SZ(A[BLOCK[l]]),pos[l],get(BIT[BLOCK[l]],pos[l]+1));
        A[BLOCK[l]].erase(A[BLOCK[l]].begin() + pos[l]-get(BIT[BLOCK[l]],pos[l]+1));
        update(BIT[BLOCK[l]],pos[l]+1);
        dsu[l] = dsu[l+1];
      }
     // trace(l,r);
      int st = BLOCK[L];MX[st]=-int(2e9);MN[st]=+int(2e9);
      int en = BLOCK[R];MX[en]=-int(2e9);MN[en]=+int(2e9);
      for(int i=0;i<SZ(A[st]);i++){
        MX[st] = max(MX[st],A[st][i]+add[st]);
        MN[st] = min(MN[st],A[st][i]+add[st]);
      }st++;
      while(st<en){
        MX[st]=-int(2e9);
        MN[st]=+int(2e9);
        st++;
      }
      st = en;
      for(int i=0;i<SZ(A[st]);i++){
        MX[st] = max(MX[st],A[st][i]+add[st]);
        MN[st] = min(MN[st],A[st][i]+add[st]);
      }
    }
    else if(t==2){
      int y;si(y);
      l = f(l);if(l>r)continue;
      int st = BLOCK[l],en = BLOCK[r];
      if(st < en){
        for(int i = (pos[l] - get(BIT[st],pos[l]+1)); i < SZ(A[st]); i++){
          A[st][i] += y;
          MX[st] = max(MX[st],add[st] + A[st][i]);
          MN[st] = min(MN[st],add[st] + A[st][i]);
        }
        st++;
      }
      while(st < en){
        MX[st] += y;
        MN[st] += y;
        add[st] += y;st++;
      }
      l = max(l,st*SQRT);l = f(l);if(l>r)continue;
     // trace(st,en,l,r);
      l = pos[l] - get(BIT[st],pos[l]+1);
      r = pos[r] - get(BIT[st],pos[r]+1);
     // trace(l,r);
      for(int i=l;i<=r;i++){
        A[st][i] += y;
        MX[st] = max(MX[st],add[st] + A[st][i]);
        MN[st] = min(MN[st],add[st] + A[st][i]);
      }
    }
    else if(t==3){
      xx++;
      l = f(l);int mx=-int(2e9),mn=+int(2e9);
      if(l>r){puts("YES");continue;}
      int st = BLOCK[l],en = BLOCK[r];
      if(st < en){
        for(int i = (pos[l] - get(BIT[st],pos[l]+1)); i < SZ(A[st]); i++){
          mx = max(mx,add[st] + A[st][i]);
          mn = min(mn,add[st] + A[st][i]);
        }
        st++;
      }
      while(st < en){
        mx = max(mx,MX[st]);
        mn = min(mn,MN[st]);
        st++;
      }
      l = max(l,st*SQRT);l = f(l);
      if(l<=r){
        l = pos[l] - get(BIT[st],pos[l]+1);
        r = pos[r] - get(BIT[st],pos[r]+1);
        for(int i=l;i<=r;i++){
          mx = max(mx,add[st] + A[st][i]);
          mn = min(mn,add[st] + A[st][i]);
        }
      }
   //   if(xx==13)trace(mx,mn);
      puts((mx<=int(1e9) && mn>=-int(1e9))?"YES":"NO");
    }
  }
  return 0;
}
