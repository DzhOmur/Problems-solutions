#include <bits/stdc++.h>

#define pb push_back
#define mk make_pair
#define fr first
#define sc second
#define int long long

using namespace std;

const int N = 3e5 + 5;

int n, x, y;

pair <int, int> a[N];

long long ans;

priority_queue < pair <int, int> > q1, q2; 

set <int> st;

main()
{
	cin >> n >> x >> y;
	
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i].fr, &a[i].sc);
	}
	sort( a + 1, a + n + 1, greater < pair <int, int> >() );
	
	for (int i = 1; i <= x; i++)
		ans += a[i].fr, q1.push( mk(-a[i].fr + a[i].sc, i) );
		
	for (int i = x + 1; i <= n; i++)
		q2.push( mk(a[i].sc, i) ), st.insert(i);
	
	while(y--)
	{
		while (!q2.empty() && !st.count(q2.top().sc) )
			q2.pop();
			
		if ( q2.empty() || (!q1.empty() && q1.top().fr + a[*st.begin()].fr > q2.top().fr ) )
		{
			ans += q1.top().fr + a[*st.begin()].fr;
			q1.pop();
			q1.push( mk( -a[*st.begin() ].fr + a[*st.begin()].sc, *st.begin() ) );
			st.erase(st.begin());
		}
		else 
		{
			ans += q2.top().fr;
			st.erase( q2.top().sc );
			q2.pop();
		}
	}
	cout << ans << endl;
}
