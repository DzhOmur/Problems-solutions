#include "gardenlib.h"
#include "garden.h"
#include <bits/stdc++.h>
//#include "grader.cpp"
 
#define fr first
#define sc second
#define mk make_pair
#define pb emplace_back
#define all(s) s.begin(), s.end()
 
using namespace std;
 
const int SZ = 200005;
 
long long n, m, p, q, k[SZ], edges[SZ][2], used[SZ][2], mn[SZ][2], last, go[2], lst, dp[SZ][2][2];
 
void dfs (int v, int type)
{
	used[v][type] = 1;
	
	int to_type;
	
	if (type == 0 || mn[v][1] == -1)
	{
		to_type = (mn[ mn[v][0] ][0] == v ? 1 : 0);
		
		if (mn[v][0] == p)
		{
			if ( to_type == 1 )
				dp[v][type][1] = 1,
				dp[v][type][0] = dp[p][1][0] + 1;
			else
				dp[v][type][0] = 1,
				dp[v][type][1] = dp[p][0][1] + 1;
			
			return;
		}
		if ( to_type == 1 && used[ mn[v][0] ][1] == 0 )
			dfs( mn[v][0], 1);
			
		else if ( used[ mn[v][0] ][0] == 0 )
			dfs( mn[v][0], 0);
			
		dp[v][type][0] = dp[ mn[v][0] ][to_type][0] + 1,
		dp[v][type][1] = dp[ mn[v][0] ][to_type][1] + 1;
	}
	else
	{
		to_type = (mn[ mn[v][1] ][0] == v ? 1 : 0);
		
		if (mn[v][1] == p)
		{
			if ( to_type == 1 )
				dp[v][type][1] = 1,
				dp[v][type][0] = dp[p][1][0] + 1;
			else
				dp[v][type][0] = 1,
				dp[v][type][1] = dp[p][0][1] + 1;
				
			return;
		}
		
		if ( to_type == 1 && used[ mn[v][1] ][1] == 0 )
			dfs( mn[v][1], 1);
		
		else if ( used[ mn[v][1] ][0] == 0 ) 
			dfs( mn[v][1], 0);
		
		dp[v][type][0] = dp[ mn[v][1] ][to_type][0] + 1,
		dp[v][type][1] = dp[ mn[v][1] ][to_type][1] + 1;
	}
}
void count_routes(int N, int M, int P, int R[][2], int Q, int G[])
{
	memset(mn, -1, sizeof(mn) );
	n = N, m = M, p = P;
	
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				dp[i][j][k] = 1e12;
	
	for (int i = 0; i < m; i++)
	{
		edges[i][0] = R[i][0], edges[i][1] = R[i][1]; 
		
		if ( mn[ edges[i][0] ][0] == -1 ) mn[ edges[i][0] ][0] = edges[i][1];
		else if ( mn[ edges[i][0] ][1] == -1 ) mn[ edges[i][0] ][1] = edges[i][1];
		
		if ( mn[ edges[i][1] ][0] == -1 ) mn[ edges[i][1] ][0] = edges[i][0];
		else if ( mn[ edges[i][1] ][1] == -1 ) mn[ edges[i][1] ][1] = edges[i][0];
	}
	q = Q;
	for (int i = 0; i < q; i++)
		k[i] = G[i];
	
	dfs(p, 0);
	dfs(p, 1);
 
	for (int i = 0; i < n; i++)
		if (!used[i][0]) dfs(i, 0);
		
	if ( dp[p][0][0] < dp[p][0][1] ) go[0] = 0;
	else go[0] = 1;
	
	if ( dp[p][1][0] < dp[p][1][1] ) go[1] = 0;
	else go[1] = 1;
	
	for (int i = 0; i < q; i++)
	{
		long long ans = 0, sup;
		
		for (int j = 0; j < n; j++)
		{
			if ( min( dp[j][0][0], dp[j][0][1] ) > k[i] ) continue;
			
			if ( dp[j][0][0] < dp[j][0][1] )
			{
				sup = k[i] - dp[j][0][0];
				
				if (sup == 0) {
					ans++;
					continue;
				}
				if (go[0] == 0 && sup % dp[p][0][0] == 0)
					ans++;
				else if (go[0] == 1)
				{
					 if ( go[1] == 0 && (sup % (dp[p][1][0] + dp[p][0][1]) == 0 || sup % (dp[p][1][0] + dp[p][0][1]) == dp[p][0][1] ) )
						ans++;
					 else if ( (sup - dp[p][0][1]) % dp[p][1][1] == 0 )
						ans++;
				}
			}
			else
			{
				sup = k[i] - dp[j][0][1];
				
				if (sup == 0){
					ans++;
					continue;
				}	
				if (go[1] == 1 && sup % dp[p][1][1] == 0)
					ans++;
				else if (go[1] == 0 )
				{
					if (go[0] == 1 && (sup % (dp[p][1][0] + dp[p][0][1]) == 0 || sup % (dp[p][1][0] + dp[p][0][1]) == dp[p][1][0]  ) )
						ans++;
					else if ( (sup - dp[p][1][0]) % dp[p][0][0] == 0 )
						ans++;
				}
			}
		}
		answer(ans);
	}
}
/**
6 6 0
1 2
0 1
0 3
3 4
4 5
1 5
1
3
**/
