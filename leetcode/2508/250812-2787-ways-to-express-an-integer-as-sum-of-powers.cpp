class Solution {
    const int MOD = 1e9 + 7;

    int getPower(int val, int x) {
        int ret = 1;
        for (int i = 0; i < x; i++) {
            ret *= val;
        }
        return ret;
    }
public:
    int numberOfWays(int n, int x) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2, power = getPower(i, x); power <= n; i++, power = getPower(i, x)) {
            for (int j = n; j >= power; j--) {
                dp[j] = (dp[j] + dp[j - power]) % MOD;
            }
        }

        return dp[n];
    }
};
