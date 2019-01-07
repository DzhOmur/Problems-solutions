/**
  Just implementation with some math...
**/
#include <bits/stdc++.h>
 
#define fr first
#define sc second
#define mk make_pair
#define pb emplace_back
#define all(s) s.begin(), s.end()
 
using namespace std;

const int N = 1e5 + 5;

int m, x1[N], yy1[N], x2[N], y2[N];

long long n, ans = 1e18;

long long compute (int j1, int j2, long long bl)
{
	if (j1 / bl == j2 / bl)
	{
		if (j1 / bl & 1)
			return (j2 - j1 + 1);
		
		return 0ll;
	}
	long long res = 0;
	
	if (j1 / bl & 1)
		res += (j1 / bl * bl + bl - j1);
	
	j1 = j1 / bl * bl + bl;
	
	if (j2 / bl & 1)
		res += (j2 % bl + 1);
		
	j2 = j2 / bl * bl - 1;
	
	long long cn = (j2 / bl - j1 / bl + 1) / 2;
	
	if ( ((j2 / bl - j1 / bl + 1) & 1) && (j2 / bl & 1) )
		cn++;
	
	res += cn * bl;
	return res;
}

long long get (int i1, int j1, int i2, int j2, long long bl)
{
	long long res = 0, cn1 = compute( j1, j2, bl ), cn2 = (j2 - j1 + 1) - cn1;
	
	if (i1 / bl == i2 / bl)
	{
		if (i1 / bl & 1)
			res += cn1 * (i2 - i1 + 1);
		else
			res += cn2 * (i2 - i1 + 1);
	}
	else
	{
		if (i1 / bl & 1)
			res += cn1 * (i1 / bl * bl + bl - i1);
		else
			res += cn2 * (i1 / bl * bl + bl - i1);
			
		i1 = i1 / bl * bl + bl;
		
		if (i2 / bl & 1)
			res += cn1 * (i2 % bl + 1);
		else
			res += cn2 * (i2 % bl + 1);
			
		i2 = i2 / bl * bl - 1;
		
		long long cn = (i2 / bl - i1 / bl + 1) / 2;
		
		if ( (i2 / bl - i1 / bl + 1) & 1 )
		{
			if ( i1 / bl % 2 == 0 )
			{
				res += (cn + 1) * cn2 * bl;
				res += cn * cn1 * bl;
			}
			else
			{
				res += (cn + 1) * cn1 * bl;
				res += cn * cn2 * bl;
			}
		}
		else
		{
			res += cn * cn1 * bl;
			res += cn * cn2 * bl;
		}
	}
	return res;
}

void calc (long long x)
{
	long long res = get(0, 0, n - 1, n - 1, x) ;
	
	for (int i = 1; i <= m; i++)
	{
		long long sup = get( x1[i], yy1[i], x2[i], y2[i], x);
		res -= sup;
		res += ( (x2[i] - x1[i] + 1) * 1ll * (y2[i] - yy1[i] + 1) - sup);
	}
	ans = min(ans, res);
	ans = min(ans, n * n - res);
}

main() 
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d %d", &x1[i], &yy1[i], &x2[i], &y2[i]);
		x1[i]--;
		yy1[i]--;
		x2[i]--;
		y2[i]--;
	}
	for (long long i = 1; i * i <= n; i++)
	{
		if ( n % i != 0 ) continue;
		calc(i);
		if (n / i != n)
			calc(n / i);
	}
	cout << ans << endl;
}
