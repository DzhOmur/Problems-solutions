/**
# dango-maker
my code
**/
#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

int n, m, ans, dp[N][3], fl[N][N][2];

char ar[N][N];

main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        scanf("\n");
        for (int j = 1; j <= m; j++)
            scanf("%c", &ar[i][j]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i > 1 && i < n && ar[i - 1][j] == 'R' && ar[i][j] == 'G' && ar[i + 1][j] == 'W')
                fl[i][j][0] = 1;

            if (j > 1 && j < m && ar[i][j - 1] == 'R' && ar[i][j] == 'G' && ar[i][j + 1] == 'W')
                fl[i][j][1] = 1;
        }
    }
    for (int d = 2; d <= n + m; d++)
    {
        memset(dp, 0, sizeof(dp));
        int last;
        for (int i = 1, j; i <= n; i++)
        {
            j = d - i;
            if ( j < 1 || j > m ) continue;

            dp[i][0] = max( dp[i - 1][0], max( dp[i - 1][1], dp[i - 1][2] ) );

            if (fl[i][j][0]) dp[i][1] = max( dp[i - 1][1], dp[i - 1][0] ) + 1;
            if (fl[i][j][1]) dp[i][2] = max( dp[i - 1][2], dp[i - 1][0] ) + 1;
            last = i;
        }
        ans += max( dp[last][0], max( dp[last][1], dp[last][2] ) );
    }
    cout << ans << endl;
}
