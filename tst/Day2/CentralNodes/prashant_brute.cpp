#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500;
const int MAXW = 1e9;

const int N = MAXN + 5;

const long long infy = 1e15;

long long a[N][N];
long long d[N][N];
long long d2[N][N];

int main() {
   int n,m; cin>>n>>m;
   assert(n <= MAXN);
   assert(m <= n * (n - 1)/2);
   for(int i = 1;i <= n;i++) {
      for(int j = 1;j <= n;j++) {
         if(i == j) a[i][j] = 0;
         else a[i][j] = infy;
      }
   }
   for(int i = 0;i < m;i++) {
      int x,y,w; scanf("%d %d %d",&x,&y,&w);
      assert(w <= MAXW);
      a[x][y] = a[y][x] = w;
   }
   for(int i = 1;i <= n;i++) {
      for(int j = 1;j <= n;j++) {
         d[i][j] = a[i][j];
      }
   }
   for(int k = 1;k <= n;k++) {
      for(int i = 1;i <= n;i++) {
         for(int j = 1;j <= n;j++) {
            d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
         }
      }
   }
   int ans = 0;
   vector<int> v;
   for(int x = 1;x <= n;x++) {
      for(int i = 1;i <= n;i++) {
         for(int j = 1;j <= n;j++) {
            if(i == j) continue;
            if(i == x || j == x) {
               d2[i][j] = infy;
            }
            else {
               d2[i][j] = a[i][j];
            }
         }
      }
      for(int k = 1;k <= n;k++) {
         for(int i = 1;i <= n;i++) {
            for(int j = 1;j <= n;j++) {
               d2[i][j] = min(d2[i][j],d2[i][k] + d2[k][j]);
            }
         }
      }
      int flag = 0;
      for(int i = 1;i <= n && !flag;i++) {
         for(int j = 1;j <= n && !flag;j++) {
            if(i == x || j == x) continue;
            if(d2[i][j] != d[i][j])
               flag = 1;
         }
      }
      if(flag) {
         ans++;
         v.push_back(x);
      }
   }
   cout<<ans<<endl;
   for(int i = 0;i < v.size();i++) {
      cout<<v[i]<<' ';
   }
   cout<<endl;
}
