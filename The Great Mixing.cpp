/**
  If we subtract n from all numbers, we just should find the minimum size of set of numbers the sum of which is equal to 0.
  This can be easily solved by bfs.
**/
#include <bits/stdc++.h>

#define fr first
#define sc second
#define pb push_back
#define mk make_pair
#define all(s) s.begin(), s.end()
 
using namespace std;

const int N = 5005;

int n, k, fl[N], dp[N], x;

queue <int> q;

main()
{
	cin >> n >> k;
	for (int i = 1; i <= k; i++)
		scanf("%d", &x), fl[x] = 1;
		
	for (int i = 0; i <= 1000; i++)
	{
		if (fl[i]){
			x = i - n;
			q.push(x + 2000);
			dp[x + 2000] = 1;
		}
	}
	while (!q.empty()){
		x = q.front();
		q.pop();
		
		for (int i = 0; i <= 1000; i++){
		
			if (fl[i]){
				int to = x + i - n;
				
				if ( to >= 0 && to <= 4000 && !dp[to] )
				{
					dp[to] = dp[x] + 1;
					q.push(to);
				}
			}
		}
	}
	if (dp[2000])
		cout << dp[2000] << endl;
	else
		cout << -1 << endl;
}
