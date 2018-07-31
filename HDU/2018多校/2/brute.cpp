#include <algorithm>
#include <cstdio>
typedef unsigned long long ll;
int mx[205], C[205][205];
ll dp[205][1005], MOD;
int main()
{
    // freopen("1002.in", "r", stdin);
    scanf("%llu", &MOD);
    for (int i = 0; i <= 200; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= 200; i++)
    {
		printf("%d\n",i);
        int LIM = i * 3.7;
        for (int j = i; j <= LIM; j++)
        {
            for (int x = 0; x < i; x++)
            {
                int v = std::min(x + 1, i - x), lim = std::min(std::min(j - v, j - v - i + x + 1), mx[x]);
                ll res = 0;
                for (int y = std::max(std::max(0, x), j - v - mx[i - x - 1]); y <= lim; y++)
                    res += dp[x][y] * dp[i - x - 1][j - v - y] % MOD * C[i - 1][x];
                dp[i][j] += res % MOD;
            }
            dp[i][j] %= MOD;
            if (dp[i][j])
                mx[i] = j;
        }
    }
    int x, y;
    while (~scanf("%d%d", &x, &y))
        printf("%llu\n", y > mx[x] ? 0 : dp[x][y]);
    return 0;
}
