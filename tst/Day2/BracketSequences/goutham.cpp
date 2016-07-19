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

const int N = 4000 + 23, mod = 1e9 + 7;
int f[N], invf[N], cat[N][N], g[N][N];
int inv[N], fac[N], invfac[N], comb[N][N];
int op[N], cl[N], len[N], corr[N], lt[N];
bool used[N];

inline void add(int& a, int b) { a += b; if (a >= mod) a -= mod; }
int mul(int a, int b) { return a * b % mod; }
int mul(int a, int b, int c) { return mul(a, mul(b, c)); }
int mul(int a, int b, int c, int d) { return mul(a, mul(b, c, d)); }

void pre()
{
	inv[1] = 1;
	for (int i = 2; i < N; i++)
		inv[i] = mod - mul(mod / i, inv[mod % i]);

	fac[0] = invfac[0] = 1;
	for (int i = 1; i < N; i++)
	{
		fac[i] = mul(fac[i - 1], i);
		invfac[i] = mul(invfac[i - 1], inv[i]);
	}

	for (int i = 0; i < N; i++)
	{
		f[i] = mul(fac[2 * i], invfac[i + 1]);
		invf[i] = mul(fac[i + 1], invfac[2 * i]);
	}

	for (int i = 0; i < N; i++)
	{
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < i; j++)
		{
			comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
			if (comb[i][j] >= mod) comb[i][j] -= mod;
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j <= i; j++)
		{
			if (j > 0) cat[i][j] = cat[i][j - 1];
			add(cat[i][j], mul(comb[i][j], f[j], f[i - j]));
		}

	for (int n = 0; n < N; n++)
		for (int k = 1; k <= 2 * n; k++)
			g[n][k] = cat[n - 1][n - 1 - k / 2];
}

#undef int
int main()
{
#define int long long
	pre();
	int n; cin >> n;
	for (int i = 1; i <= n; i++) cin >> op[i] >> cl[i];

	for (int i = 1; i <= n; i++) corr[op[i]] = cl[i];
	len[0] = n + n, corr[0] = n + n + 1;
	used[0] = used[n + n + 1] = true;

	int ret = 1;
	for (int i = 1; i <= n; i++)
	{
		int cur = fac[n - i];
		for (int j = 0; j <= n + n; j++)
			if (corr[j] > j)
				cur = mul(cur, invfac[len[j] / 2], f[len[j] / 2]);

		for (int j = 0; j <= n + n; j++) lt[j] = 0;
		stack <int> s;
		s.push(0);
		for (int j = 1; j < op[i]; j++)
		{
			if (used[j])
			{
				if (corr[j] > j) s.push(j);
				else s.pop();
				continue;
			}
			int prev = s.top(), l = len[prev];
			add(ret, mul(cur, invf[l / 2], l / 2, g[l / 2][lt[prev] + 1]));
			lt[prev]++;
		}

		int out = len[s.top()], lgt = 0;
		s.push(op[i]);
		for (int j = op[i] + 1; j < cl[i]; j++)
		{
			if (used[j])
			{
				if (corr[j] > j) s.push(j);
				else s.pop();
				continue;
			}
			if (s.top() != op[i]) continue;
			if (lgt % 2 == 0)
			{
				int now = mul(cur, invf[out / 2]);
				now = mul(now, out / 2);
				now = mul(now, comb[out / 2 - 1][lgt / 2]);
				now = mul(now, f[lgt / 2]);
				now = mul(now, f[(out - lgt) / 2 - 1]);
				add(ret, now);
			}
			lgt++;
		}

		used[op[i]] = used[cl[i]] = true;
		len[op[i]] = lgt;
		s.pop();
		len[s.top()] -= lgt + 2;
	}
	cout << ret << "\n";
	return 0;
}