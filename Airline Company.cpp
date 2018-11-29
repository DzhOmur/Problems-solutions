/**
    for all x held gcd(x, x + 1) = 1. 
    We can begin from any node and go to another node with edge that we didn't use yet. 
    We will give values to edges in increasing order, like 1,2,3...
    So every node that have 2 or more edges will have x and x+1.
**/
#include <bits/stdc++.h>

#define fr first
#define sc second
#define pb push_back
#define mk make_pair
#define all(s) s.begin(), s.end()
 
using namespace std;

const int N = 3e3 + 5;  

int n, m, u[N][N], x[N], y[N], a[N][N], sz, ans[N];

void dfs (int v)
{	
	for (int i = 1; i <= n; i++)
	{
		if (a[v][i] && u[i][v] == 0){
			u[i][v] = ++sz;
			u[v][i] = sz;
			dfs(i);
		}
	}
}

main()
{
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &x[i], &y[i]), a[x[i]][y[i]] = a[y[i]][x[i]] = 1;
		
	dfs(1);
		
	puts("YES");
	
	for (int i = 1; i <= m; i++)
		printf("%d ", u[ x[i] ][ y[i] ]);
}
