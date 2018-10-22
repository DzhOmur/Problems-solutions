#include "robots.h"
#include <bits/stdc++.h>
#define mk make_pair
#define fr first
#define sc second
 
using namespace std;
 
const int N = 1e6 + 5, M = 5e4 + 5;
 
int a, b, n;
 
pair <int, int> ar[N];
 
priority_queue <int> q;
 
inline bool check(int k, int x[], int y[])
{	
	while ( !q.empty() ) q.pop();
	
	int j = 0, cn = 0;
	for (int i = 0; i < a; i++)
	{
		while ( j < n && ar[j].fr < x[i] )
			q.push( ar[j].sc ), j++;
	
		cn = 0;
		while ( !q.empty() && cn < k )
			q.pop(), cn++;
	}
	while (j < n)
		q.push( ar[j].sc ), j++;
		
	for (int i = b - 1; i >= 0; i--)
	{
		cn = 0;
		while (!q.empty() && cn < k && q.top() < y[i])
			q.pop(), cn++;
	}
	if (q.empty())
		return true;
		
	return false;
}
bool fl = 0;
 
int putaway(int A, int B, int T, int x[], int y[], int w[], int s[]) 
{
	a = A, b = B;
	n = T;
	sort(x, x + a);
	sort(y, y + b);
	
	for (int i = 0; i < n; i++)
	{
		ar[i].fr = w[i], ar[i].sc = s[i];
		if (ar[i].fr >= x[a - 1] && ar[i].sc >= y[b - 1]) fl = 1;
	}
	if (fl) return -1;
	
	sort(ar, ar + n); 
	
	int l = -1, r = n;
	
	while (r - l > 1)
	{
		int md = (l + r) >> 1;
		if ( check(md, x, y) )
			r = md;
		else
			l = md;
	}
	return r;
}
