/**
    Let's add our edges and edges of competitor(at first our) until graph becomes mst, with kruskal's algorithm. 
    Now, there is a path between vertices of the edges that don't belong to mst.
    To satisfy the conditions, our edges must be a minimum of the weights of edges that do not belong to mst, whose vertices pass through our edges. 
**/
#include <bits/stdc++.h>

#define fr first
#define sc second
#define pb push_back
#define mk make_pair
#define all(s) s.begin(), s.end()
 
using namespace std;

const int N = 5e5 + 5;

int n, k, m, x, y, p[2][N], sz[2][N], w, tiktak;

long long ans;

vector < vector <pair <int, int> > > g;

int get (int v, int type)
{
	return v == p[type][v] ? v : p[type][v] = get(p[type][v], type);
}
void unite (int a, int b, int type)
{
	a = get(a, type);
	b = get(b, type);
	if (a != b){
		if (sz[type][a] > sz[type][b]) swap(a, b);
		p[type][a] = b;
		sz[type][b] += sz[type][a];
	}
}
vector < pair <int, pair <int, int> > > vec;

multiset <pair <int, int> > st[N];

void dfs2 (int v, int p = 0, bool fl = 0)
{
	for (auto to : g[v])
	{
		if (to.fr == p) continue;
		dfs2( to.fr, v, to.sc );
		
		if ( st[to.fr].size() > st[v].size() ) st[v].swap(st[to.fr]);
		
		for (auto it : st[to.fr])
		{
			if (st[v].count(it))
				st[v].erase(it);
			else
				st[v].insert(it);
		}
	}
	if (fl)
	{
		if (st[v].empty() ){
			puts("-1");
			exit(0);
		}
		ans += st[v].begin()->fr;
	}
}
main()
{
	cin >> n >> k >> m;
	
	g.resize(n + 1);
	
	for (int i = 1; i <= n; i++)
		p[0][i] = i, sz[0][i] = 1,
		p[1][i] = i, sz[1][i] = 1;
		
	for (int i = 1; i <= k; i++){
		scanf("%d%d", &x, &y);
		unite(x, y, 0);
		g[x].pb( {y, 1} );
		g[y].pb( {x, 1} );
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &x, &y, &w);
		
		if ( get(x, 1) == get(y, 1) ) continue;
		
		if ( get(x, 0) == get(y, 0) ) {
			vec.pb( mk( w, mk(x, y) ) );
			continue;
		}
		unite(x, y, 0);
		unite(x, y, 1);
		g[x].pb( mk(y, 0) );
		g[y].pb( mk(x, 0) );
	}
	for (auto it : vec)
	{	
		st[it.sc.fr].insert( { it.fr, ++tiktak } );
		st[it.sc.sc].insert( { it.fr, tiktak } );
	}
	dfs2(1);
	
	cout << ans << endl;
}
