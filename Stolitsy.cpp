/**
  Explanation coming soon
**/
#include <bits/stdc++.h>
   
#define fr first
#define sc second
#define mk make_pair
#define pb emplace_back
#define all(s) s.begin(), s.end()
  
using namespace std;
 
const int N = 1e5 + 5;
 
int n, d, x, y, cnt[N], used[N], res[N], cn, dp1[N], dp2[N], par[N];
 
vector < vector <int> > g;
 
int dfs (int v, int sz, int &cen, int p = 0)
{   
    int sum = 1;
     
    for (auto to : g[v]){
        if (to == p || used[to]) continue;
        sum += dfs(to, sz, cen, v);
    }
    if ( cen == 0 && (sum * 2 >= sz || p == 0) )
        cen = v;
     
    return sum;
}
void add (int v, int p, int val, int dist)
{
    if (dist < d) cnt[dist] += val;
    else
        return;
         
    for (auto to : g[v])
    {
        if (to == p || used[to]) continue;
        add( to, v, val, dist + 1 );
    }
}
void calc (int v, int p, int dist)
{
    if (dist == d)
        res[v]++, cn++;
    else if (dist < d)
        res[v] += cnt[d - dist];
         
    for (auto to : g[v])
    {
        if (to == p || used[to]) continue;
        calc(to, v, dist + 1);
    }
}
void build (int v, int sz)
{
    int cen = 0;
    dfs(v, sz, cen);
     
     
    for (auto to : g[cen])
    {
        if (used[to]) continue;
        add( to, cen, +1, 1 );
    }   
    cn = 0;
    for (auto to : g[cen])
    {
        if (used[to]) continue;
        add(to, cen, -1, 1);
        calc( to, cen, 1 );
        add(to, cen, +1, 1);
    }
    for (auto to : g[cen])
    {
        if (used[to]) continue;
        add( to, cen, -1, 1 );
    }   
    res[cen] += cn;
    used[cen] = 1;
     
    for (auto to : g[cen])
    {
        if (!used[to])
            build( to, sz >> 1 );
    }
}
multiset <int> st[N];
 
void dfs1 (int v, int p = 0, int h = 0)
{
    par[v] = p;
     
    st[v].insert(h);
     
    for (auto to : g[v])
    {
        if (to == p) continue;
        dfs1(to, v, h + 1);
         
        if (st[to].size() > st[v].size() ) st[v].swap(st[to]);
         
        for (auto it : st[to] )
            st[v].insert(it);
    }
    dp1[v] = st[v].count( h + d );
    dp2[v] = st[v].count( h + d - 1 );
}
long long old[4], now[4], ans;
 
main()
{
    cin >> n >> d;
     
    if (d & 1){
        puts("0");
        return 0;
    }
    d >>= 1;
     
    g.resize(n + 1);
     
    for (int i = 1; i < n; i++)
        scanf("%d%d", &x, &y),
        g[x].pb(y),
        g[y].pb(x);
         
    build( 1, n );
     
    dfs1(1);
     
    for (int i = 1; i <= n; i++)
    {
        memset(old, 0, sizeof(old) );
        memset(now, 0, sizeof(now) );
         
        vector <int> vec;
        for (auto to : g[i]){
            if (to != par[i])
                vec.pb( dp2[to] );
        }
        vec.pb( res[i] - dp1[i] );  
         
        old[0] = 1;
        for (auto it : vec)
        {
            for (int j = 1; j <= 3; j++)
                now[j] += old[j], now[j] += old[j - 1] * it;
             
            now[0] = old[0];
             
            for (int j = 0; j <= 3; j++)
                old[j] = now[j], now[j] = 0;
        }
        ans += old[3];
    }
    cout << ans << endl;
}
