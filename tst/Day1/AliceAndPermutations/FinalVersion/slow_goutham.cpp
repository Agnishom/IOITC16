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

const int N = 10;
int ans[N][N];

void pre()
{
	for (int n = 1; n < N; n++)
	{
		int p[n + 1];
		for (int i = 1; i <= n; i++) p[i] = i;
		do
		{
			int sp[n + 1];
			for (int i = 1; i <= n; i++) sp[i] = p[i];

			int num = 0;
			while (true)
			{
				bool done = true;
				for (int i = 1; i <= n; i++)
					if (p[i] != i)
						done = false;
				if (done) break;

				for (int i = 1; i <= n - 1; i++)
					if (p[i] > p[i + 1])
						swap(p[i], p[i + 1]);
				num++;
			}

			for (int i = num; i <= n; i++) ans[n][i]++;
			for (int i = 1; i <= n; i++) p[i] = sp[i];
		}
		while (next_permutation(p + 1, p + n + 1));
	}
}

int main()
{
	pre();
	int t; cin >> t;
	while (t--)
	{
		int n, k; cin >> n >> k;
		if (k > n) k = n;
		cout << ans[n][k] << "\n";
	}
	return 0;
}