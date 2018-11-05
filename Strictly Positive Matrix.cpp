#include <bits/stdc++.h>
 
using namespace std;

const int N = 2005;

int n, ar[N][N], pos, used[N], used2[N];

void dfs (int v)
{
	used[v] = 1;
	for (int i = 1; i <= n; i++)
		if (ar[v][i] && !used[i])
			dfs(i);
}
void dfs2 (int v)
{
	used2[v] = 1;
	for (int i = 1; i <= n; i++)
		if (ar[i][v] && !used2[i])
			dfs2(i);
}

int main() 
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)	
			scanf("%d", &ar[i][j]);
	}
	dfs(1);
	dfs2(1);
	
	for (int i = 1; i <= n; i++)
	{
		if ( !used[i] || !used2[i] )
		{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
}
