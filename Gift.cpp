#include <bits/stdc++.h>

#define pb emplace_back
#define mk make_pair
#define fr first
#define sc second

using namespace std;

const int N = 1e6 + 5;

int n, k, sz, l[N];

long long sum, ar[N], mx, cn, mn[N];

vector < pair <long long, int> > vec[N];

vector < vector <int> > ans;

main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		scanf("%lld", &ar[i]), sum += ar[i], mx = max(mx, ar[i]);
		
	if (mx > sum / k || sum % k != 0){
		puts("-1");
		return 0;
	}
	sum /= k;
	for (int i = 1; i <= n; i++)
	{
		if (cn + ar[i] > sum){
			
			vec[sz].pb( make_pair(sum - cn, i) );
			ar[i] -= (sum - cn);
			i--;
			cn = 0;
			sz++;
		}
		else{
			cn += ar[i];
			vec[sz].pb( make_pair(ar[i], i) );
		}
		if (cn == sum){
			cn = 0;
			sz++;
		}
	}
	assert(sz == k);
	
	while (1)
	{
		ans.pb( vector <int>() );
		
		mn[ans.size()] = 2e18;
		
		for (int j = 0; j < sz; j++)
			mn[ans.size()] = min(vec[j][ l[j] ].fr, mn[ans.size()]);
		
		for (int j = 0; j < sz; j++)
		{
			ans.back().pb( vec[j][ l[j] ].sc );
			
			vec[j][ l[j] ].fr -= mn[ ans.size() ];
			
			if (vec[j][ l[j] ].fr == 0)
				l[j]++;
		}
		if (l[0] >= (int)vec[0].size() ) break;
	}
	cn = 0;
	cout << ans.size() << endl;
	for (auto it : ans)
	{
		printf("%lld ", mn[ cn + 1 ]);
		for (auto to : it)
			printf("%d ", to);
			
		puts("");
		cn++;
	}
}
/**
4 2
2 3 3 2
**/
