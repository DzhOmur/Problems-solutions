#include <bits/stdc++.h>

#define mk make_pair
#define pb push_back
#define fr first
#define sc second

using namespace std;

const int N = 5e5 + 5;

int n;
long long ar[N], ans;

vector <pair <long long, int> > vec;

int main() 
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%I64d", &ar[i]);
		
	vec.pb( mk( 1e18, 0 ) );
		
	for (int i = 1; i <= n; i++)
	{
		int l = 0, r = vec.size();
		while (r - l > 1)
		{
			int md = (l + r) >> 1;
			if ( vec[md].fr > ar[i] )
				l = md;
			else
				r = md;
		}
		ans += vec.back().sc - vec[l].sc;
		
		if (l != 0) ans++;
		
		while (vec.back().fr < ar[i])
			vec.pop_back();	
		
		if (vec.back().fr == ar[i])
			vec.back().sc++;
		else
			vec.push_back( mk( ar[i], vec.back().sc + 1 ) );
	}
	cout << ans << endl;
}
