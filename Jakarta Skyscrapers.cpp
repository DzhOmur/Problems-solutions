/**
	If doge's power is P and standing point is V, we can jump to all V - k * P >= 0 and V + k * P < n.
	let's denote TO, the points in which we can jump. 
	If our power is P and point TO also have power P. It isn't necessary to consider other points which come after TO.
**/
#include <bits/stdc++.h>
 
#define mk make_pair
#define pb push_back
#define fr first
#define sc second
 
using namespace std;
 
const int N = 3e4 + 5;
 
int n, m, en, pos, p, d[N], st;
 
set <int, greater <int> > vec[N];
 
vector < vector <pair <int, int> > > g;
 
priority_queue < pair <int, int> > q;
 
int main() 
{
	cin >> n >> m;
	g.resize(n);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &pos, &p);
		vec[pos].insert(p);
		if (i == 1)
			st = pos;
		if (i == 2)
			en = pos;
	}
	for (int i = 0; i < n; i++)
	{
		for (auto to : vec[i])
		{
			for (int j = i - to; j >= 0; j -= to)
			{
				g[i].pb(mk(j, (i - j) / to ) );
				if (vec[j].lower_bound(to) != vec[j].end() && *vec[j].lower_bound(to) == to)
					break;
			}
			for (int j = i + to; j < n; j += to)
			{
				g[i].pb(mk(j, (j - i) / to ) );
				if (vec[j].lower_bound(to) != vec[j].end() && *vec[j].lower_bound(to) == to)
					break;
			}
		}
	}
	memset(d, 0x3f3f3f3f, sizeof(d));
	d[st] = 0;
	q.push( mk( 0, st ) );
	
	while (!q.empty())
	{
		int v = q.top().sc, len = -q.top().fr;
		q.pop();
		if (d[v] < len) continue;
		
		for (auto to : g[v])
		{
			if (d[to.fr] > d[v] + to.sc)
			{
				d[to.fr] = d[v] + to.sc;
				q.push( mk( -d[to.fr], to.fr ) );
			}
		}
		
	}
	if (d[en] > 1e9)
		d[en] = -1;
	cout << d[en] << endl;
}
