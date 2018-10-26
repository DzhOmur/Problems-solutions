#include <bits/stdc++.h>

#define mk make_pair
#define pb push_back
#define fr first
#define sc second

using namespace std;

const int N = 1e5 + 5;

int n, m, par, c[N], l[N], tin[N], ar[N], timer, tout[N], root[N], sz;

long long ans;

struct st
{
	int l, r, cnt;
	long long sum;
};
st t[N * 31];

vector < vector <int> > g;

void dfs (int v, int p = 0)
{
	tin[v] = ++timer;
	
	ar[ tin[v] ] = v;
	
	for (auto to : g[v])
	{
		if (to == p) continue;
		dfs(to, v);
	}
	
	tout[v] = timer;
}
void update (int ov, int nv, int val, int tl = 1, int tr = 1e9)
{
	if (tl == tr)
		t[nv].sum = t[ov].sum + tl,
		t[nv].cnt = t[ov].cnt + 1;
	else
	{
		int tm = (tl + tr) >> 1;
		if (val <= tm)
		{
			if(!t[nv].l) t[nv].l = ++sz;
			t[nv].r = t[ov].r;
			update( t[ov].l, t[nv].l, val, tl, tm );
		}
		else
		{
			if(!t[nv].r) t[nv].r = ++sz;
			t[nv].l = t[ov].l;
			update( t[ov].r, t[nv].r, val, tm + 1, tr );
		}
		t[nv].cnt = t[ t[nv].l ].cnt + t[ t[nv].r ].cnt;
		t[nv].sum = t[ t[nv].l ].sum + t[ t[nv].r ].sum;
	}
}
int get (int ov, int nv, int M, int tl = 1, int tr = 1e9)
{	
	if (tl == tr)
		return min( M / tl, (t[nv].cnt - t[ov].cnt) );
	
	int tm = (tl + tr) >> 1;
	
	if (t[ t[nv].l ].sum - t[ t[ov].l ].sum >= M)
		return get( t[ov].l, t[nv].l, M, tl, tm);
		
	return get( t[ov].r, t[nv].r, M - (t[ t[nv].l ].sum - t[ t[ov].l ].sum) ,tm + 1, tr) + t[ t[nv].l ].cnt - t[ t[ov].l ].cnt;
}
int main() 
{
	cin >> n >> m;
	g.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &par, &c[i], &l[i]);
		if (par) g[ par ].pb(i);
	}
	dfs(1);
	for (int i = 1; i <= n; i++)
	{
		root[i] = ++sz;
		update( root[i - 1], root[i], c[ar[i]] );
	}
	for (int i = 1; i <= n; i++)
		ans = max( ans, get( root[ tin[i] - 1 ], root[ tout[i] ], m ) * 1ll * l[i] );
		
	cout << ans << endl;
}



