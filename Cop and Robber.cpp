#include "coprobber.h"
#include <bits/stdc++.h>
#include "grader.cpp"

#define mk make_pair
#define pb push_back
#define fr first
#define sc second

using namespace std;

const int M = 505;

int n, win[2][M][M], ar[M][M], to[M][M], deg[M][M], ind1, ind2;

queue <pair <pair <int, int>, int > > q;

int start(int N, bool A[MAX_N][MAX_N])
{
	n = N;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			ar[i][j] = A[i-1][j-1];
			for (int k = 1; k <= n; k++)
				deg[k][i] += ar[i][j];
		}
	}
	for (int i = 1; i <= n; i++)
	{
		win[0][i][i] = 1;
		win[1][i][i] = 1;
		q.push( mk( mk(i, i), 0 ) );
		q.push( mk( mk(i, i), 1 ) );
	}
	while (!q.empty())
	{
		int x = q.front().fr.fr, y = q.front().fr.sc, type = q.front().sc;
		q.pop();
		
		for (int i = 1; i <= n; i++)
		{
			if ( type == 1 && ar[x][i] == 0 && i != x ) continue;
			if ( type == 0 && ar[y][i] == 0 ) continue;
			
			if ( type == 1 && !win[0][i][y] )
			{
				to[i][y] = x;
				win[0][i][y] = 1;
				q.push( mk( mk(i, y), 0 ) );
			}
			if (type == 0 && !win[1][x][i] && --deg[x][i] == 0 )
			{
				win[1][x][i] = 1;
				q.push( mk( mk(x, i), 1 ) );
			}
		}
	}
	bool fl = 1;
	for (int j = 1; j <= n; j++)
	{
		if (win[0][1][j] == 0) fl = 0;
	}
	if (fl)
		ind1 = 1;
	ind1--;
	return ind1;
}

int nextMove(int R)
{
	ind2 = R;
    return ind1 = to[ind1 + 1][ind2 + 1] - 1;
}
