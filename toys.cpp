#include <bits/stdc++.h>
 
#define mk make_pair
#define pb push_back
#define fr first
#define sc second
 
using namespace std;
 
int n;
 
vector <int> vec;
deque <int> en;
 
map <int, set <int> > mp;
 
int main() 
{
	cin >> n;
	en.pb(n);
	for (int i = 2; i * i <= n; i++)
	{
		if (n % i != 0) continue;
		vec.pb(i);
		if (i != n / i)
			en.push_front(n / i);
	}
	for (auto to : en)
		vec.pb(to);
	mp[1].insert(0);
	
	for (int i = 0; i < (int)vec.size(); i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (vec[i] % vec[j] != 0) continue;
			for (auto to : mp[ vec[i] / vec[j] ])
				mp[ vec[i] ].insert( to + vec[j] - 1 );
		}
	}
	cout << mp[n].size() << endl;
	for (auto to : mp[n])
		printf("%d ", to);
}
