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

const int N = 1e5 + 23, mod = 1e9 + 7;
int f[N];

int power(int a, int b)
{
	if (b == 0) return 1;
	if (b & 1) return power(a, b - 1) * 1ll * a % mod;
	return power(a * 1ll * a % mod, b / 2);
}

int main()
{
	f[0] = 1;
	for (int i = 1; i < N; i++)
		f[i] = f[i - 1] * 1ll * i % mod;
	int t; cin >> t;
	while (t--)
	{
		int n, k; cin >> n >> k;
		if (k >= n) k = n;
		cout << f[k] * 1ll * power(k + 1, n - k) % mod << "\n";
	}
	return 0;
}