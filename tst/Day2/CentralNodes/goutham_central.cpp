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

const int N = 500 + 23, inf = 0x3f3f3f3f;
vector < pair <int, int> > adj[N];
bool central[N];
int dist[N], par[N];
set < pair <int, int> > s;

void dij(int p)
{
	for (int i = 0; i < N; i++) dist[i] = inf;
	for (int i = 0; i < N; i++) par[i] = -1;
	dist[p] = 0;
	s.insert(make_pair(0, p));
	while (!s.empty())
	{
		int u = (s.begin() -> second);
		s.erase(s.begin());
		for (pair <int, int> q : adj[u])
		{
			int v = q.first;
			int wt = q.second;
			if (dist[v] < dist[u] + wt) continue;
			else if (dist[v] > dist[u] + wt)
			{
				s.erase(make_pair(dist[v], v));
				dist[v] = dist[u] + wt;
				par[v] = u;
				s.insert(make_pair(dist[v], v));
			}
			else par[v] = -1;
		}
	}
	for (int i = 0; i < N; i++)
		if (par[i] != p and ~par[i])
			central[par[i]] = true;
}

#undef int
int main()
{
#define int long long
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(make_pair(v, w));
		adj[v].push_back(make_pair(u, w));
	}
	for (int i = 1; i <= n; i++) dij(i);
	int tot = 0;
	for (int i = 1; i <= n; i++)
		if (central[i])
			tot++;
	cout << tot << "\n";
	for (int i = 1; i <= n; i++)
		if (central[i])
			cout << i << " ";
	cout << "\n";
	return 0;
}