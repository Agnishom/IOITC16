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

const int maxn = 1e5 + 500;
int p[maxn], deg[maxn] = { }, odd = 0;

int main()
{
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	for(int i = 2; i <= n; i++)
	{
		cin >> p[i];
		deg[i]++; deg[p[i]]++;
	}
	for(int i = 1; i <= n; i++) odd += deg[i] % 2;

	cout << odd/2 << '\n';
	
	int q;
	cin >> q;
	while(q--)
	{
		int v, u;
		cin >> v >> u;
		
		if(deg[p[v]] % 2 == 1) odd--;
		else odd++;
		deg[p[v]]--;
		
		p[v] = u;

		if(deg[p[v]] % 2 == 1) odd--;
		else odd++;
		deg[p[v]]++;

		cout << odd/2 << '\n';
	}

	return 0;
}
