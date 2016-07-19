#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cassert>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long

const int N = 1048600, inf = 0x3f3f3f3f;
int MX, val[N], cost[N], dp[N][21];

int go(int n, int l, int bit)
{
   int& ret = dp[n][l];
   if (~ret) return ret;
   
   int sz = 0;
   for (int i = 0; i <= 20; i++)
      if (n >> i & 1)
         sz = i;
   
   ret = 0;
   if (l <= sz)
   {
      if (bit == 0 and val[n >> l] != val[n])
         ret = cost[n];
      if (bit == 1 and val[n >> l] - l != val[n])
         ret = cost[n];
   }
   if (l == sz + 1) ret = cost[n];
   
   int curval = val[n];
   if (l <= sz)
   {
      if (bit == 0) curval = val[n >> l];
      else curval = val[n >> l] - l;
   }
   if (l == sz + 1) curval = inf;
   
   int lft = n + n, rht = lft + 1;
   if (lft < MX)
   {
      int cur1 = go(lft, l + 1, bit);
      if (val[lft] <= curval - bit)
         cur1 = min(cur1, go(lft, 0, bit));
      int cur2 = go(rht, l + 1, bit);
      if (val[rht] <= curval - bit)
         cur2 = min(cur2, go(rht, 0, bit));
      ret += cur1 + cur2;
   }
   return ret;
}

#undef int
int main()
{
#define int long long
   int h; scanf("%lld", &h);
   MX = 1 << h;
   for (int i = 1; i < MX; i++) scanf("%lld", val + i);
   for (int i = 1; i < MX; i++) scanf("%lld", cost + i);
   memset(dp, -1, sizeof(dp));
   int bit; scanf("%lld", &bit);
   printf("%lld\n", min(go(1, 0, bit), go(1, 1, bit)));
   return 0;
}