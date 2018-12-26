/**
    Make bfs from r and s to find out the distances from these vertices to others.
    Then for each node(denote it as v) calculate the current maximum of the minimum values(distances from r) of nodes that are on some path from f to v. Denote these values as res[v].
    It can be calculated using bfs, which start on f. 
    If we did't visit the vertex(denote it as u) , there is edge between v and u, the value is equal to min( res[v], distance from r to u ), 
    otherwise the value is equal to max(res[u], res[v]).
    The answer is res[s].
**/
#include <bits/stdc++.h>
  
#define fr first
#define sc second
#define mk make_pair
#define pb emplace_back
#define all(s) s.begin(), s.end()
 
using namespace std;

vector < vector <int> > g;

const int N = 1e5 + 5;

int n, m, x, y, d[2][N], r, f, s, res[N], used[N];

queue <int> q;

void bfs (int type, int v)
{
	d[type][v] = 1;
	q.push(v);
	
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		for (auto to : g[v]){
			if (d[type][to] == 0)
			{
				d[type][to] = d[type][v] + 1;
				q.push(to);
			}
		}
	}
}
void dfs (int v)
{
	q.push(v);
	used[v] = 1;
	
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		
		res[v] = min( res[v], d[0][v] );
		
		for (auto to : g[v])
		{
			if (d[1][v] - 1 == d[1][to])
			{	
				if (!used[to]){
					res[to] = min( res[v], res[to] );
					used[to] = 1;
					q.push(to);	
				}
				else
					res[to] = max( res[to], res[v] );
			}
		}
	}
}
main()
{
	cin >> n >> m;
	g.resize(n + 1);
	
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &x, &y),
		g[x].pb(y), g[y].pb(x);
	
	cin >> s >> f >> r;
	
	bfs(0, r);
	bfs(1, s);
	
	for (int i = 1; i <= n; i++)
		res[i] = 1e9 + 7;
	
	dfs(f);
	
	cout << res[s] - 1 << endl;
}
