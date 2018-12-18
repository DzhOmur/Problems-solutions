#include <bits/stdc++.h>
 
#define fr first
#define sc second
#define mk make_pair
#define pb emplace_back
#define all(s) s.begin(), s.end()
 
using namespace std;
 
const int N = 1e5 + 5;
 
int dp[25][1025][1025], p[N], n, ar[N], k, ans, ind[25][1025][1025], last, path[N], sz, cn[N];
 
main()
{
	freopen("subsequence.in", "r", stdin);
	freopen("subsequence.out", "w", stdout);
	for (int j = 0; j < 1024; j++)
		cn[j] = __builtin_popcount(j);
		
	cin >> n;
	
	for (int i = 1; i <= n; i++)
		scanf("%d", &ar[i]);
		
	for (int i = 1; i <= n; i++){
		scanf("%d", &k);
		
		int pref = (ar[i] >> 10);
		int suf = ar[i] - (pref << 10), res = 0;
		
		for (int j = 0; j < 1024; j++)
		{
			if ( cn[ j & suf ] <= k && dp[ k - cn[ j & suf ] ][pref][j] > res )
			{
				res = dp[ k - cn[ j & suf ] ][pref][j];
				p[i] = ind[ k - cn[ j & suf ] ][pref][j];
			}
		}
		res++;
		
		if (res > ans){
			ans = res;
			last = i;
		}
		
		for (int j = 0; j < 1024; j++){
			if (res > dp[cn[pref & j] ][j][suf])
			{
				dp[cn[pref & j] ][j][suf] = res;
				ind[cn[pref & j] ][j][suf] = i;
			}
		}
	}
	cout << ans << endl;
	
	while (ans--){
		path[++sz] = last;
		last = p[last];
	}
	for (int i = sz; i >= 1; i--)
		printf("%d ", path[i]);
}
