#include<bits/stdc++.h>
#define assn(n,a,b) assert(n<=b and n>=a)
using namespace std;
typedef long long LL;
LL h[100];
#define LIM 1000000000000000000ll


LL getval(LL a, LL d, LL maxt, LL lim){
    if(lim < a) return 0;
    return min(maxt, (lim-a)/d  + 1);
}

LL get(LL x, LL y, LL n){
    LL ret=0;
    for(LL it=n, a=0; it>=0; a+=h[it]+1, it--){
        if(a > x)break;
        if(it==0)ret += getval(-a, 6, 1ll<<(n-1), y), ret += getval(-a+4, 6, 1ll<<(n-1), y);
        else ret += getval(-a, h[it+2]+1, (1ll<<(n-it)), y);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    LL n,xc,yc,q;
    cin >> n >> xc >> yc >> q;
    assn(xc,0ll,LIM);
    assn(yc,0ll,LIM);
    assn(n,1,60);

    h[1]=1,h[2]=2;
    for(int i=3; i<=n+2; i++)
        h[i]=2*h[i-1]+1;

    while(q--){
        LL x1,y1,x2,y2,ans=0;
        cin >> x1 >> y1 >> x2 >> y2;
        assn(x1,0ll,LIM);
        assn(y1,0ll,LIM);
        assn(x2,0ll,LIM);
        assn(y2,0ll,LIM);

        assert(y2>=y1 and x2>=x1);

        x1-=xc,x2-=xc,y1-=yc,y2-=yc;
        ans = get(x2, y2, n) - get(x1-1, y2, n) - get(x2, y1-1, n) + get(x1-1,y1-1, n);
        cout << ans << endl;
    }
    return 0;
}


