#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<stack>
#include<cmath>
#include<iomanip>
#include<cstdlib>
#include<sstream>
#include<climits>
#include<cassert>
#include<time.h>

using namespace std;
#define f(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) f(i,0,n)
#define pb push_back
#define ss second
#define ff first
#define vi vector<int>
#define vl vector<ll>
#define s(n) scanf("%d",&n)
#define ll long long
#define mp make_pair
#define PII pair <int ,int >
#define PLL pair<ll,ll>
#define inf 1000*1000*1000+5
#define v(a,size,value) vi a(size,value)
#define sz(a) a.size()
#define all(a) a.begin(),a.end()
#define tri pair < int , PII >
#define TRI(a,b,c) mp(a,mp(b,c))
#define xx ff
#define yy ss.ff
#define zz ss.ss
#define in(n) n = inp()
#define vii vector < PII >
#define vll vector< PLL >
#define viii vector < tri >
#define vs vector<string>
#define DREP(a) sort(all(a)); a.erase(unique(all(a)),a.end());
#define INDEX(arr,ind) (lower_bound(all(arr),ind)-arr.begin())
#define ok if(debug)
#define trace1(x) ok cerr << #x << ": " << x << endl;
#define trace2(x, y) ok cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)    ok      cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)  ok cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " \
                                << #d << ": " << d << endl;
#define trace5(a, b, c, d, e) ok cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " \
                                     << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) ok cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " \
                                    << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;

#define read(a) freopen(a,"r",stdin)
#define write(a) freopen(a,"w",stdout)
ll MOD = int(1e9) + 7;

int debug = 0;
const int N = int(2e3) + 5;
using namespace std;
ll powmod(ll a,ll b)
{
        ll ret = 1;
        while(b)
        {
                if(b&1)
                     (ret *= a) %= MOD;
                b >>= 1;
                a = a*a%MOD;
        }
        return ret;
}

inline ll div1(ll a , ll b)
{
        return a * powmod(b,MOD-2) % MOD;
}

ll C[N];
ll g[N][N],h[N][N];
int a[N],op[N],cl[N];
int len[N],par[N];
int leninpar[N];
ll fact[N];
int main()
{
        int i,j,n,t;
        ios::sync_with_stdio(false);
        fact[0] = 1;
        f(i,1,N)fact[i] = (ll)i * fact[i-1]%MOD;
        C[0] = 1;
        C[2] = 1;
        for(i = 4; i < 2*N;i += 2)
        {
                for(j = i-1; j >= 0;j--)
                {
                        (C[i] += (C[j]*C[i-j-2]) ) %= MOD;
                }
                if(i < 20 && C[i])trace2(i,C[i]);
        }
        for(n = 2; n < N;n += 2)
        {
                for(i = n - 1;i >= 1;i--)
                {
                        g[n][i] = (g[n][i+1] + C[i-1]*C[n-i-1])%MOD;
                        //h[n][i]  = (h[n][i-1] + g[n][i]) % MOD;
                        if(n <= 10)trace3(n,i,g[n][i]);
                }

        }
        for(n = 1; n < N;n++)
        {
                for(i = 1; i <= n;i++)
                {
                        h[n][i] = (h[n][i-1] + g[n][i]) % MOD;
                        if(n <= 10)trace3(n,i,h[n][i]);
                }
        }

        cin>>n;
        rep(i,n)
        {
                cin>>op[i+1]>>cl[i+1];
        }
        op[0] = 0;cl[0] = 2*n+1;
        len[0] = 2*n;
        ll prod = C[2*n];
        ll ans = 0;
        f(i,1,2*n+1)leninpar[i] = i;
        for(i = 1; i <= n; i++ )
        {
                trace1(i);
                int ind = 0;
                int mainpar = 0;
                for(j = op[i] - 1; j > 0; j--)
                {
                        if(a[j] > 0 && cl[a[j]] > i)
                                mainpar  = ind = a[j];
                }
                trace1(mainpar);
                for(j = op[i] - 1; j >= 1; j--)
                {
                        if( a[j] == 0 )
                        {
                                ll toadd = g[len[ind]][leninpar[j]] * div1(prod,C[len[ind]]) % MOD;
                                (toadd *= fact[n-i]) %= MOD;
                                (ans += toadd) %= MOD;
                                trace5(j,fact[n-i],len[ind],leninpar[j],toadd);
                                trace2(prod,C[len[ind]]);
                        }
                        if(a[j] < 0)
                        {
                                ind = -a[j];
                        }
                        if(a[j] > 0)
                        {
                                ind = par[j];
                        }
                }
                trace1(ans);
                for(j = leninpar[cl[i]]-1; j >= leninpar[op[i]] + 1;j--)
                {
                        int st = leninpar[op[i]];
                        ll mul = C[j-st-1] * C[len[ind] - (j-st) - 1 ] % MOD;
                        ll toadd = div1(prod,C[len[ind]]) * mul;
                        (ans += (toadd * fact[n-i])) %= MOD;
                        trace5(j,st,toadd,len[ind],prod);
                }



                a[op[i]] = i;
                a[cl[i]] = -i;
                int bal = 0,curind = 0;
                for(j = op[i] + 1; j < cl[i]; j++)
                {
                        if(a[j] == 0 && bal == 0)
                        {
                                leninpar[j] = ++curind;
                        }
                        if(bal == 0)par[j] = i;
                        if(a[j] < 0)bal--;
                        if(a[j] > 0)bal++;
                }
                len[i] = curind;
                bal = 0;curind = 0;
                for(j = op[mainpar] + 1; j < cl[mainpar]; j++)
                {
                        if(a[j] == 0 && bal == 0)leninpar[j] = ++curind;
                        if(a[j] < 0)bal--;
                        if(a[j] > 0)bal++;
                }
                prod = div1(prod,C[len[mainpar]]);
                prod = prod*C[len[i]]%MOD;
                len[mainpar] -= (len[i] + 2);
                prod = prod*C[len[mainpar]]%MOD;
                trace4(ans,len[i],len[mainpar],mainpar);

        }

        cout<<ans+1;
}
