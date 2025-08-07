class Solution {
    int executeRupdp(const vector<vector<int>> &fruits, vector<vector<int>> &dp) {
        const int n = fruits.size(), dp_n = dp[0].size();

        dp[0][0] = fruits[0][n - 1];
        for (int i = 1; i < n - 1; i++) {
            vector<int> &curdp = dp[i % 2], &prevdp = dp[1 - (i % 2)];
            
            int prev_j = n - 1 - max(n - 1 - (i - 1), i);
            int start = max(n - 1 - i, i + 1);
            for (int j = start; j < n; j++) {
                int dp_j = n - 1 - j;

                curdp[dp_j] = 0;

                if (dp_j <= prev_j) curdp[dp_j] = prevdp[dp_j];
                if (dp_j < prev_j) curdp[dp_j] = max(curdp[dp_j], prevdp[dp_j + 1]);
                if (0 < dp_j) curdp[dp_j] = max(curdp[dp_j], prevdp[dp_j - 1]);

                curdp[dp_j] += fruits[i][j];
            }
        }

        return dp[(n - 2) % 2][0];
    }

    int executeLdowndp(const vector<vector<int>> &fruits, vector<vector<int>> &dp) {
const int n = fruits.size(), dp_n = dp[0].size();

        dp[0][0] = fruits[n - 1][0];
        for (int i = 1; i < n - 1; i++) {
            vector<int> &curdp = dp[i % 2], &prevdp = dp[1 - (i % 2)];
            
            int prev_j = n - 1 - max(n - 1 - (i - 1), i);
            int start = max(n - 1 - i, i + 1);
            for (int j = start; j < n; j++) {
                int dp_j = n - 1 - j;

                curdp[dp_j] = 0;

                if (dp_j <= prev_j) curdp[dp_j] = prevdp[dp_j];
                if (dp_j < prev_j) curdp[dp_j] = max(curdp[dp_j], prevdp[dp_j + 1]);
                if (0 < dp_j) curdp[dp_j] = max(curdp[dp_j], prevdp[dp_j - 1]);

                curdp[dp_j] += fruits[j][i];
            }
        }

        return dp[(n - 2) % 2][0];
    }
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        const int n = fruits.size();
        int ret = 0;

        for (int i = 0; i < n; i++) {
            ret += fruits[i][i]; fruits[i][i] = 0;
        }

        vector<vector<int>> dp(2, vector<int>((n + 1) / 2));

        ret += executeRupdp(fruits, dp);
        ret += executeLdowndp(fruits, dp);

        return ret;
    }
};
