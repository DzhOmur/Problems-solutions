/**
  if ( abs(a[i] - b[j]) > k )
    dp[i][j] = dp[i - 1][j - 1] + 1;
  else
    dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1;
    
   k <= 10, So if we are considering dp[i][1..n], all dp[i][j] is equal to dp[i-1][j-1] + 1, except of maximum 2*k elements.
   We just compute all DP, like dp[i][j] = dp[i - 1][j - 1] + 1, 
   and for every layer of dp --> such as 1<=i<=n, we compute with brute force to 2*k elements, which abs(a[i] - b[j]) <= k. 
**/

#include <bits/stdc++.h>

#define fr first
#define sc second
#define pb push_back
#define mk make_pair
#define all(s) s.begin(), s.end()
 
using namespace std;

const int N = 5e5 +	 5;

int n, k, x[N], t[N * 4], pos[N], ar[N], y[N];

inline void push(int v, int tl, int tr)
{
	if (tl != tr)
	{
		t[v + v] += t[v];
		t[v + v + 1] += t[v];
		t[v] = 0;
	}
}
int get (int pos, int v = 1, int tl = 0, int tr = n + n)
{
	push(v, tl, tr);
	
	if (tl == tr)
		return t[v];
	
	int tm = (tl + tr) >> 1;
	
	if (pos <= tm)
		return get(pos, v + v, tl, tm);
		
	return get(pos, v + v + 1, tm + 1, tr);
}
void update (int l, int r, int val, int v = 1, int tl = 0, int tr = n + n)
{
	push(v, tl, tr);
	
	if (l > tr || tl > r)
		return;
	
	if (l <= tl && tr <= r)
	{
		t[v] += val;
		push(v, tl, tr);
		return ;
	}
	
	int tm = (tl + tr) >> 1;
	
	update( l, r, val, v + v, tl, tm );
	update( l, r, val, v + v + 1, tm + 1, tr );
}
main() 
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		scanf("%d", &x[i]), pos[ x[i] ] = i;
		
	for (int i = 1; i <= n; i++)
		scanf("%d", &y[i]);
		
	for (int i = n; i <= n + n; i++)
		ar[i] = i - n;
		
	vector <int> vec;
		
	for (int i = n - 1; i >= 0; i--)
	{
		vec.clear();
		ar[i] = n - i;
		
		for (int j = max(1, y[n - i] - k); j <= min(n, y[n - i] + k); j++)
			vec.pb(pos[j]);
			
		sort( all(vec) );
		
		for (auto ind : vec)
		{
			ar[ind + i] = min( get(ind + i - 1) + ar[ind + i - 1] + (ind + i - 1 != i), ar[ind + i + 1] + get(ind + i + 1));
			update(ind + i, ind + i, -get(ind + i) );
		}
		update(i + 1, i + n, 1);	
	}
	cout << ar[n] + get(n) << endl;
}
