class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        const int n = nums.size() / 3;

        priority_queue<int> pq;
        long long sum_first = 0;
        for (int i = 0; i < n; i++) {
            pq.push(nums[i]);
            sum_first += nums[i];
        }

        vector<long long> dp = {sum_first};
        for (int i = 0; i < n; i++) {
            if (pq.top() > nums[n + i]) {
                sum_first -= pq.top();
                pq.pop();
                pq.push(nums[n + i]);
                sum_first += nums[n + i];
            }

            dp.push_back(sum_first);
        }

        long long sum_second = 0;
        priority_queue<int, vector<int>, greater<>> second_pq;
        for (int i = 0; i < n; i++) {
            second_pq.push(nums[3 * n - 1 - i]);
            sum_second += nums[3 * n - 1 - i];
        }

        long long ans = dp[n] - sum_second;
        for (int i = n - 1; i >= 0; i--) {
            if (second_pq.top() < nums[n + i]) {
                sum_second += nums[n + i] - second_pq.top();
                second_pq.pop();
                second_pq.push(nums[n + i]);
            }
            ans = min(ans, dp[i] - sum_second);
        }

        return ans;
    }
};
