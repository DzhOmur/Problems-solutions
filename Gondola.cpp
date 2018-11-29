#include "gondola.h"
#include <bits/stdc++.h>

#define fr first
#define sc second
#define pb push_back
#define mk make_pair
#define all(s) s.begin(), s.end()

using namespace std;

const int N = 3e5 + 5, mod = 1e9 + 9;

int sz, mx, pos, ind[N], ar[N], n, fl;

deque <pair <int, int> > vec;

map <int, int> u;

int valid(int N, int x[])
{
	n = N;
	for (int i = 0; i < n; i++)
	{
		if (u.count(x[i]))
			return 0;
		u[x[i]] = i + 1;	
	}
	for (int i = 1; i < n; i++)	
	{
		if ( u[i] != 0 && u[i + 1] != 0 && ((u[i] - 1) + 1) % n != u[i + 1] - 1)
			return 0;
	}
	if ( u[n] != 0 && u[1] != 0 && ((u[n] - 1) + 1) % n != u[1] - 1)
		return 0;
		
	return 1;
}	
int replacement(int n, int a[], int ans[])
{
	for (int i = 0; i < n; i++)
		mx = max(a[i], mx);
		
	for (int i = 0; i < n; i++)
	{
		if(a[i] > n)
			vec.pb( mk(a[i], i) );
		else
			pos = (i - (a[i] - 1) + n) % n;
	}
	sort( all(vec) );
	ind[pos] = ++sz;
	
	for (int i = (pos + 1) % n; i != pos; i = (i + 1) % n)
		ind[i] = ++sz;
	
	sz = 0;
	for (int i = n + 1; i <= mx; i++)
	{
		ans[sz++] = ind[ vec[0].second ];
		ind[ vec[0].second ] = i;
		if ( vec[0].first == i )
			vec.pop_front();
	}
	return sz;
}
int binpow (int a, int b)
{
	if (b == 0)
		return 1;
		
	if (b & 1)
		return a * 1ll * binpow(a, b - 1) % mod;
		
	int res = binpow(a , b >> 1);
	
	return res * 1ll * res % mod;
}
int countReplacement(int n, int a[])
{
	long long ans = 1;
	if (valid(n, a) == 0)
		return 0;
		
	for (int i = 0; i < n; i++)
		mx = max(a[i], mx);
		
	for (int i = 0; i < n; i++)
	{
		if(a[i] > n)
			vec.pb( mk(a[i], i) );
		else
			pos = (i - (a[i] - 1) + n) % n, fl = 1;
	}
	sort( all(vec) );
	
	int L = n + 1;
	
	sz = vec.size();
	for (auto to : vec)
	{
		if (to.first != L){
			ans *= binpow( sz, (to.first - L) ),
			ans %= mod;
		}
		L = to.first + 1;
		sz--;
	}
	if (!fl)
		ans *= n, ans %= mod;
		
	return ans;
}
