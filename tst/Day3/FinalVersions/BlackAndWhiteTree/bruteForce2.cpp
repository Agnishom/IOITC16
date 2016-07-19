#include <bits/stdc++.h>

using namespace std;

const int N = 2e6;

int val[N];
int p[N];

int a[N];
int b[N];
int c[N];

int main() {
  int n,q; cin>>n>>q;
  for(int i = 1;i <= n;i++) {
    scanf("%d",val+i);
    assert(val[i] == 0 || val[i] == 1);
  }
  for(int i = 2;i <= n;i++) {
    scanf("%d",p+i);
    assert(p[i] < i && p[i] >= 1);
  }
  while(q--) {
    char type; cin>>type;
    if(type == 'K') {
      int u,v,k; scanf("%d %d %d",&u,&v,&k);
      int cc = u;
      int as = 0,bs = 0;
      while(cc) {
        a[as++] = cc;
        cc = p[cc];
      }
      cc = v;
      while(cc) {
        b[bs++] = cc;
        cc = p[cc];
      }
      reverse(a,a+as);
      reverse(b,b+bs);
      int p1 = 0,p2 = 0;
      while(a[p1] == b[p2] && p1 < as && p2 < bs) p1++,p2++;
      int cnt = 0;
      for(int i = as - 1;i >= p1;i--) {
        cnt+=val[a[i]];
        if(cnt == k) {
          printf("%d\n",a[i]);
          break;
        }
      }
      if(cnt == k) continue;
      cnt+=val[a[p1 - 1]];
      if(cnt == k) {
        printf("%d\n",a[p1 - 1]);
        continue;
      }
      for(int i = p2;i < bs;i++) {
        cnt+=val[b[i]];
        if(cnt == k) {
          printf("%d\n",b[i]);
          break;
        }
      }
      if(cnt < k) 
        printf("-1\n");
    }
    else if(type == 'T') {
      int u; scanf("%d",&u);
      val[u] = 1 - val[u];
    }
    else {
      int u,v; scanf("%d %d",&u,&v);
      p[u] = v;
      assert(v < u);
    }
  }
}
