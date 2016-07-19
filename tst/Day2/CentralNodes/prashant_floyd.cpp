#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500;
const long long MAXW = 1e9;

const int N = MAXN + 5;

const long long infy = 5e8;

long long a[N][N];
long long d[N][N];
long long c[N][N];

const long long MOD = 1e9 + 7;

long long mul(long long a,long long b) {
   return a * b % MOD;
}

void add(long long &a,long long b) {
   a+=b;
   if(a >= MOD) a-=MOD;
}

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
         if(a[i][j] != infy && i != j) c[i][j] = 1;
      }
   }
   for(int k = 1;k <= n;k++) {
      for(int i = 1;i <= n;i++) {
         for(int j = 1;j <= n;j++) {
            if(d[i][k] + d[k][j] < d[i][j]) {
               c[i][j] = mul(c[i][k],c[k][j]);
               d[i][j] = d[i][k] + d[k][j];
            }
            else if(d[i][k] + d[k][j] == d[i][j] && k != i && k != j) {
               add(c[i][j],mul(c[i][k],c[k][j]));
            }
         }
      }
   }
   vector<int> ans;
   for(int i = 1;i <= n;i++) {
      int flag = 0;
      for(int j = 1;j <= n && !flag;j++) {
         for(int k = 1;k <= n && !flag;k++) {
            if(j == i || k == i || k == j) continue;
            if(a[i][j] == infy || a[i][k] == infy) continue;
            if(d[j][i] + d[i][k] != d[j][k]) continue;
            if(mul(c[j][i],c[i][k]) == c[j][k]) {
               flag = 1;
               ans.push_back(i);
            }
         }
      }
   }
   cout<<ans.size()<<endl;
   for(int i = 0;i < ans.size();i++) {
      cout<<ans[i]<<' ';
   }
   cout<<endl;
}
