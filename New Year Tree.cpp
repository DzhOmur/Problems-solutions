/**
  We know that diameter of tree is the distance between the most distant vertex from root(denote it v), and the most distant vertex from v.
  
  So if new vertex is the farthest from our root, we just increase answer, and update the farthest vertex.
  Else our answer can only be increased by the path between v and new vertex.
**/

#include <bits/stdc++.h>
  
#define fr first
#define sc second
#define mk make_pair
#define pb push_back
#define all(s) s.begin(), s.end()
  
using namespace std;
 
const int N = 2e6 + 5;
 
int q, n = 4, up[20][N], h[N], ans = 2, x[N], mx = 2, farthest = 2, tin[N], tout[N], tiktak;
 
vector <int> g[N];
 
void dfs (int v, int p = 0)
{
	tin[v] = ++tiktak;
	h[v] = h[p] + 1;
	up[0][v] = p;

	for (int l = 1; l < 20; l++)
		up[l][v] = up[l - 1][ up[l - 1][v] ];
	
	for (auto to : g[v])
		dfs(to, v);
		
	tout[v] = ++tiktak;
}
bool upper (int a, int b)
{
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}
int lca (int a, int b)
{
	if (upper(a, b)) return a;
	if (upper(b, a)) return b;
	
	for (int l = 19; l >= 0; l--)
	{
		if (up[l][a] && !upper(up[l][a], b))
			a = up[l][a];
	}
	return up[0][a];
}
int main() 
{
	g[1].pb(2);
	g[1].pb(3);
	g[1].pb(4);

	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		scanf("%d", &x[i]);
		g[x[i]].pb(++n);
		g[x[i]].pb(++n);
	}
	dfs(1);
	
	n = 4;
	
	for (int i = 1; i <= q; i++)
	{
		++n;
		++n;
		if ( h[ x[i] ] == mx ){
			ans++;
			mx++;
			farthest = n;
		}else{
			int LCA = lca(n, farthest);
			
			if (h[n] - h[LCA] + h[farthest] - h[LCA] > ans)
				ans++;
		}
		printf("%d\n", ans);
	}
}
