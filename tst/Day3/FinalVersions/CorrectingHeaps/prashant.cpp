#include <bits/stdc++.h>

using namespace std;

const int N = 1048600;
const int MAXC = 1000;
const int MAXA = 1000000000;
const int infy = 2000000000;

int a[N];
int c[N];

int dp[N][21];

int main() {
   int H; cin>>H;
   int n = (1<<H);
   assert(H <= 20);
   a[0] = infy;
   for(int i = 1;i < n;i++) {
      scanf("%d",a+i);
      assert(1 <= a[i] && a[i] <= MAXA);
   }
   for(int i = 1;i < n;i++) {
      scanf("%d",c+i);
      assert(1 <= c[i] && c[i] <= MAXC);
   }
   int type; cin>>type;
   assert(type == 0 || type == 1);
   for(int i = n - 1;i >= 1;i--) {
      for(int j = 0,v = i;;j++,v/=2) {
         if(2 * i >= n)
            dp[i][j] = ((a[v] - j * type) != a[i]) * c[i];
         else {
            int l = dp[2 * i][j + 1];
            if( type == 0 && a[v] >=  a[2 * i] ) l = min(l,dp[2 * i][0]);
            else if(type == 1 && (a[v] - j) > a[2 * i] ) l = min(l,dp[2 * i][0]);
            int r = dp[2 * i + 1][j + 1];
            if( type == 1 && (a[v] - j) > a[2 * i + 1] ) r = min(r,dp[2 * i + 1][0]);
            else if(type == 0 && a[v] >= a[2 * i + 1]) r = min(r,dp[2 * i + 1][0]);
            dp[i][j] = ((a[v] - j * type) != a[i]) * c[i] + l + r;
         }
         if(v == 0) break;
      }
   }
   cout<<min(dp[1][0],dp[1][1])<<endl;
}
