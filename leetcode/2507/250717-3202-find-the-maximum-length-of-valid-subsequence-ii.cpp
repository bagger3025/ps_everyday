class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        const int n = nums.size();

        vector<vector<int>> dp(n, vector<int>(k, 1));

        int maxval = 1;
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                int t = (nums[i] + nums[j]) % k;
                dp[i][t] = max(dp[i][t], dp[j][t] + 1);
                maxval = max(maxval, dp[i][t]);
            }
        }

        return maxval;
    }
};
