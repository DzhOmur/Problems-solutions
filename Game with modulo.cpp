#include <bits/stdc++.h>

#define pb emplace_back
#define mk make_pair
#define fr first
#define sc second
#define all(s) s.begin(), s.end()

using namespace std;

string s;

int res;

void ask (int a, int b)
{
	printf("? %d %d\n", a, b);
	fflush(stdout);
	char ch;
	cin >> ch;
	if(ch == 'x')
		res = 1;
	else
		res = 0;
}

main()
{	
	while (cin >> s)
	{
		if (s == "end") break;

		int l = 0, r = 0, L;
		
		ask(0, 1);
		
		if (res)
			l = 0, r = 1, L = l;
		
		for (int i = 0; i < 30; i++)
		{
			if (r) break;
			ask( (1 << i), (1 << (i + 1) ) );
			if (res)
				l = (1 << i), r = (1 << (i + 1)), L = l;
		}
		while (r - l > 1)
		{
			int md = (l + r) >> 1;
			ask ( L, md );
			if (res)
				r = md;
			else
				l = md;
		}
		printf("! %d\n", r);
	}
}
