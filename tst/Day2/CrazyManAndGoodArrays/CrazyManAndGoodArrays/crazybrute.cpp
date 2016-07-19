#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <queue>
#include <map>
#include <stack>
#include <cmath>
#include <cstring>
#include <tuple>
#include <cassert>

using namespace std;

long long mult[100005] = { }, add[100005] = { };

int main()
{
	ios::sync_with_stdio(false);

	int n, q;
	cin >> n >> q;

	while(q--)
	{
		int t, l, r;
		cin >> t >> l >> r;
		if(t == 3)
		{
			bool ans = true;
			for(int i = l; i <= r; i++)
			{
				if((add[i] > 1e9 || add[i] < -1e9) && mult[i] == 0)
				{
					ans = false;
					break;
				}
			}
			if(ans) cout << "YES\n";
			else cout << "NO\n";
		}
		else
		{
			int k;
			cin >> k;
			if(k == 0) continue;
			if(t == 1)
			{
				for(int i = l; i <= r; i++)	mult[i] += k;
			}
			if(t == 2)
			{
				for(int i = l; i <= r; i++)	add[i] += k;
			}
		}
	}

	return 0;
}