#include <bits/stdc++.h>

using namespace std;

const int N = 1030;
const int MAXC = 1000;
const int MAXA = 1000000000;
const int infy = 2000000000;

int a[N];
int b[N];
int c[N];

int dp[N][N];

int main() {
   int H; cin>>H;
   assert(H <= 10);
   int n = (1<<H) - 1;
   for(int i = 1;i <= n;i++) {
      cin>>a[i];
      b[i] = a[i];
   }
   for(int i = 1;i <= n;i++) {
      cin>>c[i];
   }
   int type; cin>>type;
   assert(type == 0);
   sort(b+1,b+n+1);
   map<int,int> mp;
   mp[b[1]] = 1;
   for(int i = 2;i <= n;i++) {
      if(b[i] != b[i - 1]) {
         mp[b[i]] = mp[b[i - 1]] + 1;
      }
   }
   int m = mp[b[n]];
   for(int i = 1;i <= n;i++) {
      a[i] = mp[a[i]];
   }
   
   for(int i = n;i >= 1;i--) {
      for(int j = 1;j <= m;j++) {
         dp[i][j] = (a[i] != j) * c[i];
         if(2 * i <= n) {
            int l = dp[2 * i][j];
            if(a[2 * i] <= j) l = min(l,dp[2 * i][a[2 * i]]);
            int r = dp[2 * i + 1][j];
            if(a[2 * i + 1] <= j) r = min(r,dp[2 * i + 1][ a[2 * i + 1] ]);
            dp[i][j]+=l + r;
         }
      }
   }
   cout<<min(dp[1][m],dp[1][a[1]])<<endl;
}
