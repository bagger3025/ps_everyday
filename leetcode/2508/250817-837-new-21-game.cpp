class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if (n >= k + maxPts - 1) return 1.;

        vector<double> dp(n + 1);
        dp[0] = 1;
        const double equal_prob = 1. / maxPts;

        double cur_prob = 0;
        for (int i = 1; i <= k; i++) {
            cur_prob += dp[i - 1];
            if (i > maxPts) {
                cur_prob -= dp[i - maxPts - 1];
            }
            dp[i] = cur_prob * equal_prob;
        }
        
        double ans = dp[k];
        for (int i = k + 1; i <= n; i++) {
            if (i > maxPts) {
                cur_prob -= dp[i - maxPts - 1];
            }
            ans += cur_prob * equal_prob;
        }
        return ans;
    }
};
