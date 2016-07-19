#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

const int MOD = 1e9 + 7;

int fact[N];


int solve(int n,int k) {
   if(k >= n) return fact[n];
   else return (long long)(k + 1) * solve(n - 1,k) % MOD;
}

int main() {
   fact[0] = 1;
   for(int i = 1;i <= 1e5;i++) {
      fact[i] = (long long)fact[i - 1] * i % MOD;
   }
   int t; cin>>t;
   assert(t <= 100);
   while(t--) {
      int n,k; cin>>n>>k;
      assert(n <= 1e5 && k <= 1e5);
      cout<<solve(n,k)<<endl;
   }
}
