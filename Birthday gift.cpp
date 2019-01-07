/**
  The observation is that we can just find adjacent pair that their lca is equal to v.
**/

#include <bits/stdc++.h>
 
#define fr first
#define sc second
#define mk make_pair
#define pb emplace_back
#define all(s) s.begin(), s.end()
 
using namespace std;

const int N = 2e5 + 5;

int n, m, q, x, y, up[20][N], h[N], a[N], type, l, r;

vector < vector <int> > g; 

void dfs (int v, int p = 0)
{
	h[v] = h[p] + 1;
	
	up[0][v] = p;
	for (int i = 1; i < 20; i++)
		up[i][v] = up[i - 1][ up[i - 1][v] ];
		
	for (auto to : g[v])
	{
		if (to == p) continue;
		dfs(to, v);
	}
}
int lca (int a, int b)
{
	if(h[a] > h[b]) swap(a, b);
	
	int cnt = h[b] - h[a];
	
	for (int i = 19; i >= 0; i--)
	{
		if (cnt & (1 << i) )
			b = up[i][b];
	}
	if (a == b) return a;
	
	assert( h[a] == h[b] );
	
	for (int i = 19; i >= 0; i--)
	{
		if (up[i][a] != up[i][b])
			a = up[i][a], b = up[i][b];
	}
	return up[0][a];
}
set < pair <int, int> > st, st2;

main() 
{
	cin >> n >> m >> q;
	g.resize(n + 1);
	
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		g[x].pb(y);
		g[y].pb(x);
	}
	dfs(1);
	
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &a[i]);
		if (i > 1)
			st.insert( mk( lca( a[i - 1], a[i] ), i - 1 ) );
			
		st2.insert( mk(a[i], i) );
	}
	while (q--)
	{
		scanf("%d%d%d", &type, &l, &r);
		
		if (type == 1){
			st2.erase( mk(a[l], l) );
			if (l > 1)
				st.erase( mk( lca( a[l - 1], a[l] ), l - 1 ) );
			if (l < m)
				st.erase( mk( lca( a[l], a[l + 1] ), l ) );
			a[l] = r;
			if (l > 1)
				st.insert( mk( lca( a[l - 1], a[l] ), l - 1 ) );
			if (l < m)
				st.insert( mk( lca( a[l], a[l + 1] ), l ) );
			st2.insert( mk(a[l], l) );
		}
		else{
			scanf("%d", &x);
			auto it = st2.lower_bound( mk(x, l) );
			if ( it != st2.end() && it->fr == x && it->sc <= r )
				printf("%d %d\n", it->sc, it->sc);
			else
			{
				auto it = st.lower_bound( mk( x, l ) );
				if ( it != st.end() && it->fr == x && it->sc + 1 <= r )
					printf("%d %d\n", it->sc, it->sc + 1);
				else
					printf("-1 -1\n");
			}
		}
	}
}
