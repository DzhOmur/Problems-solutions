#include <bits/stdc++.h>

#define fr first
#define sc second
#define mk make_pair
#define pb emplace_back
#define all(s) s.begin(), s.end()

using namespace std;

const int N = 2e5 + 5;

int n, m, x, y, root, a[N];

int dp[N][505], tin[N], tiktak, inf = 1e9 + 7;

vector < vector <int> > g;

vector < pair <int, int> > vec;

void dfs (int v)
{
	if (g[v].empty() )
		tin[v] = ++tiktak;
		
	for (auto to : g[v]){
		dfs(to);
		
		if (!tin[v])
			tin[v] = tin[to];
		else
			tin[v] = min( tin[v], tin[to] ); 
	}
	vec.pb( mk( tiktak, v ) );
}

main() 
{
	cin >> n >> m;
	g.resize(n + 1);
	
	for (int i = 1; i <= n; i++){
		scanf("%d%d", &x, &a[i]);
		if (x == 0)
			root = i;
		else
			g[x].pb(i);
	}
	dfs(root);
	
	sort( all(vec) );
	
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			dp[i][j] = -inf;
			
	dp[0][0] = 0;
	
	for (auto it : vec)
	{	
		for (int j = 1; j <= m; j++)
			dp[it.fr][j] = max( dp[ tin[it.sc] - 1 ][j - 1] + a[it.sc], dp[it.fr][j] );
			
		for (int j = 0; j <= m; j++)
			dp[it.fr][j] = max( dp[it.fr][j], dp[it.fr - 1][j] );
	}
	cout << dp[vec.back().fr][m] << endl;
}
