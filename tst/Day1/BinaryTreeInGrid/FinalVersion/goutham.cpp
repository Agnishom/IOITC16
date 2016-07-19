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

int get(int u, int v, int r)
{
	int sum = (1ll << (v + 1)) - (1ll << u);
	if (-sum > r) return 0;
	if (sum <= r) return (1ll << (v - u + 1));
	return ((r + sum) >> (u + 1)) + 1;
}

int go(int n, int k, int l, int r)
{
	if (n == 1)
	{
		int ret = 0;
		ret += (l <= -2 and -2 <= r);
		ret += (l <= 2 and 2 <= r);
		return ret;
	}
	if (k == 1)
		return go(n, k + 1, l - 2, r - 2) + go(n, k + 1, l + 2, r + 2);
	while (r % 3) r--;
	while (l % 3) l++;
	if (l > r) return 0;
	return get(k - 2, n - 2, r / 3) - get(k - 2, n - 2, l / 3 - 1);
}

#undef int
int main()
{
#define int long long
	int f[66];
	f[1] = 2, f[2] = 3;
	for (int i = 3; i < 66; i++) f[i] = f[i - 1] << 1;

	int n, x, y, q;
	scanf("%lld%lld%lld%lld", &n, &x, &y, &q);

	while (q--)
	{
		int x1, y1, x2, y2;
		scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
		int curx = x, ret = (x1 <= x and x <= x2 and y1 <= y and y <= y2);
		for (int i = n; i >= 1; i--)
		{
			curx += f[i];
			if (curx < x1) continue;
			if (curx > x2) break;
			ret += go(n, i, y1 - y, y2 - y);
		}
		cout << ret << "\n";
	}
	return 0;
}
