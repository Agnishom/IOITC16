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

struct node
{
	int lo, hi, add;
	bool enabled;
} tree[300000] = { };
int trstp = 1;

void merge(int i)
{
	tree[i].lo = 2e9;
	tree[i].hi = -2e9;
	if(tree[2*i].enabled)
	{
		tree[i].lo = min(tree[i].lo, tree[2*i].lo);
		tree[i].hi = max(tree[i].hi, tree[2*i].hi);
	}
	if(tree[2*i + 1].enabled)
	{
		tree[i].lo = min(tree[i].lo, tree[2*i + 1].lo);
		tree[i].hi = max(tree[i].hi, tree[2*i + 1].hi);
	}
}
void split(int i)
{
	tree[2*i].add += tree[i].add;
	tree[2*i].lo += tree[i].add;
	tree[2*i].hi += tree[i].add;
	tree[2*i + 1].add += tree[i].add;
	tree[2*i + 1].lo += tree[i].add;
	tree[2*i + 1].hi += tree[i].add;
	tree[i].add = 0;
}
void disable(int root, int u, int v, int s = 1, int e = trstp)
{
	if(e < u || v < s) return;
	if(u <= s && e <= v)
	{
		tree[root].enabled = false;
		return;
	}
	split(root);
	int mid = (s + e)/2;
	disable(2*root, u, v, s, mid);
	disable(2*root + 1, u, v, mid + 1, e);
	merge(root);
}

void update(int root, int u, int v, int add, int s = 1, int e = trstp)
{
	if(e < u || v < s) return;
	if(u <= s && e <= v)
	{
		tree[root].add += add;
		tree[root].lo += add;
		tree[root].hi += add;
		return;
	}
	split(root);
	int mid = (s + e)/2;
	update(2*root, u, v, add, s, mid);
	update(2*root + 1, u, v, add, mid + 1, e);
	merge(root);
}

pair<int,int> query(int root, int u, int v, int s = 1, int e = trstp)
{
	if(!tree[root].enabled || e < u || v < s) return {+2e9, -2e9};
	if(u <= s && e <= v) return {tree[root].lo, tree[root].hi};
	split(root);
	int mid = (s + e)/2;
	auto x = query(2*root, u, v, s, mid);
	auto y = query(2*root + 1, u, v, mid + 1, e);
	merge(root);
	return {min(x.first, y.first), max(x.second, y.second)};
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, q;
	cin >> n >> q;
	while(trstp < n) trstp *= 2;
	for(int i = 0; i < trstp + n; i++) tree[i].enabled = true;

	int qs = 0;
	while(q--)
	{
		int t, l, r;
		cin >> t >> l >> r;
		if(t == 3)
		{
			qs++;
			auto x = query(1, l, r);
			//if(qs == 203){ cout << x.first << ' ' << x.second << '\n';
			if(-1e9 <= x.first && x.second <= 1e9) cout << "YES\n";
			else cout << "NO\n";
		}
		else
		{
			int k;
			cin >> k;
			if(k == 0) continue;
			if(t == 1) disable(1, l, r);
			if(t == 2) update(1, l, r, k);
		}
	}

	return 0;
}
