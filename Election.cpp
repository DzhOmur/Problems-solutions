#include <algorithm>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <iomanip>
#include <utility>
#include <math.h>
#include <time.h>
#include <vector>
#include <set>
#include <map>
 
#define fr first
#define sc second
#define mk make_pair
#define pb push_back
#define sz(s) (int)s.size()
#define all(s) s.begin(), s.end()
 
using namespace std;
 
const int N = 5e5 + 5;
 
int n, tests, L, R, ans[N];
 
pair <int, int> t[N * 4];
 
char s[N];
 
vector < pair <int, int> > vec[N];
 
vector <int> st;
 
pair <int, int> combine (pair <int, int> a, pair <int, int> b)
{
    pair <int, int> c = mk( a.fr + b.fr, min( b.sc, a.sc + b.fr ) );
    return c;
}
 
void build (int v = 1, int tl = 1, int tr = n)
{
    if (tl == tr)
        t[v].fr = (s[tl] == 'C' ? 1 : -1), t[v].sc = t[v].fr;
    else
    {
        int tm = (tl + tr) >> 1;
        build( v + v, tl ,tm );
        build( v + v + 1, tm + 1 ,tr );
 
        t[v] = combine( t[v + v], t[v + v + 1] );
    }
}
void update (int pos, int val, int v = 1, int tl = 1, int tr = n)
{
    if (tl == tr)
        t[v] = mk( val, val );
    else
    {
        int tm = (tl + tr) >> 1;
        if (pos <= tm)
            update( pos, val, v + v, tl, tm );
        else
            update( pos, val, v + v + 1, tm + 1, tr );
 
        t[v] = combine( t[v + v], t[v + v + 1] );
    }
}
pair <int, int> get (int l, int r, int v = 1, int tl = 1, int tr = n)
{
    if (tl > r || l > tr)
        return mk(0, 0);
 
    if (l <= tl && tr <= r)
        return t[v];
 
    int tm = (tl + tr) >> 1;
 
    return combine( get(l, r, v + v, tl, tm), get(l, r, v + v + 1, tm + 1, tr) );
}
main()
{
    cin >> n;
    scanf("%s", s + 1);
    cin >> tests;
 
    for (int i = 1; i <= tests; i++)
    {
        scanf("%d%d", &L, &R);
        vec[L].pb( mk(R, i) );
    }
    build ();
 
    for (int i = n; i >= 1; i--)
    {
        if (s[i] == 'T')
        {
            update(i, 0);
            st.pb(i);
        }
        else if (!st.empty() )
        {
            update(st.back(), -1);
            st.pop_back();
        }
        for (auto to : vec[i])
        {
            int res = upper_bound( st.rbegin(), st.rend(), to.fr ) - st.rbegin();
            res += max(0, -get( i, to.fr ).sc );
            ans[to.sc] = res;
        }
    }
    for (int i = 1; i <= tests; i++)
        printf("%d\n", ans[i]);
}
