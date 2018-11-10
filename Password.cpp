#include <bits/stdc++.h>

#define fr first
#define sc second
#define mk make_pair
#define pb push_back
#define sz(s) (int)s.size()
#define all(s) s.begin(), s.end()

using namespace std;

const int N = 10005, inf = 1e9 + 7;

int n, k, l, a[N], x, b[N], d[25][N], in, pos[N], dp[1 << 22];

queue <int> q;

main()
{
    cin >> n >> k >> l;

    for (int i = 1; i <= k; i++){
        scanf("%d", &x);
        a[x] = 1;
    }
    for (int i = 0; i <= n; i++){
        if (a[i] != a[i + 1])
            a[i] = 1;
        else
            a[i] = 0;
    }
    for (int i = 1; i <= l; i++)
        scanf("%d", &b[i]);

    for (int i = 0; i <= n; i++)
    {
        if (!a[i]) continue;
        pos[in] = i;
        d[in][i] = 1;
        q.push(i);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            for (int i = 1; i <= l; i++)
            {
                if(v - b[i] >= 0 && d[in][v - b[i]] == 0)
                {
                    d[in][v - b[i]] = d[in][v] + 1;
                    if ( a[v - b[i]] == 0 )
                        q.push(v - b[i]);
                }
                if(v + b[i] <= n && d[in][v + b[i]] == 0)
                {
                    d[in][v + b[i]] = d[in][v] + 1;
                    if ( a[v + b[i]] == 0 )
                        q.push(v + b[i]);
                }
            }
        }
        in++;
    }
    for (int i = 0; i <in; i++)
        for (int j = 0; j <= n; j++)
            d[i][j] = (d[i][j] == 0 ? inf : d[i][j] - 1);

    memset(dp, 0x3f3f3f3f, sizeof(dp));
    dp[0] = 0;

    for (int mask = 1; mask < (1 << in); mask++)
    {
        for (int j = 0; j < in; j++){
            if ( ( mask & (1 << j) ) == 0 ) continue;

            for (int o = j + 1; o < in; o++)
            {
                if ( ( mask & (1 << j) ) == 0 ) continue;
                dp[mask] = min( dp[mask], dp[mask ^ (1 << j) ^ (1 << o)] + d[j][ pos[o] ] );
            }
            break;
        }
    }
    if (dp[ (1 << in) - 1 ] > 1e9)
        cout << -1 << endl;
    else
        cout << dp[ (1 << in) - 1 ] << endl;
}
