/**
  sz[v] - it's size of subtree v
  s[v] - it's set of subtree's sizes
  if we know size of 1 splitted tree, we can find optimal sizes of 2 other.
  We are using small to large to avoid time limit.
**/
#include <bits/stdc++.h>

#define mk make_pair
#define pb push_back
#define fr first
#define sc second

using namespace std;

const int N = 2e5 + 5;

int n, x, y, sz[N], ans = 1e9 + 7;

vector < vector <int> > g;

set <int> s[N];

inline  void upd (int a, int b, int c)
{
	ans = min( ans, max( a, max(b, c) ) - min( a, min(b, c) ) );
}

void dfs (int v, int p = 0)
{
	sz[v] = 1;
	int big = -1;
	for (auto to : g[v])
	{
		if (to == p) continue;
		dfs(to, v);
		sz[v] += sz[to];
		if (big == -1 || s[to].size() > s[big].size())
			big = to;
		
		auto pos = s[to].lower_bound( (sz[to] + 1) / 2 );
		
		if (pos != s[to].end() )
			upd( sz[to] - *pos, n - (sz[to] - *pos) - *pos, *pos );
		
		if (pos != s[to].begin())
		{
			pos--;
			upd( sz[to] - *pos, n - (sz[to] - *pos) - *pos, *pos );
		}
	}
	if (big != -1)
	{
		s[v].swap(s[big]);
		
		for (auto to : g[v])
		{
			if (to == p || to == big) continue;
			for (auto it : s[to])
			{
				auto pos = s[v].lower_bound( (n - it + 1) / 2 );
				
				if (pos != s[v].end() )
					upd( it, n - it - *pos, *pos );
				
				if (pos != s[v].begin())
				{
					pos--;
					upd(it, n - it - *pos, *pos);
				}
			}
		}
		for (auto to : g[v])
		{
			if (to == p || to == big) continue;
			for (auto it : s[to])
				s[v].insert(it);
		}
	}
	s[v].insert(sz[v]);
}

int main() 
{
	cin >> n;
	g.resize(n + 1);
	for (int i = 1; i < n; i++)
		scanf("%d%d", &x, &y),
		g[x].pb(y), g[y].pb(x);
		
	dfs(1);
	
	cout << ans << endl;
}
close
