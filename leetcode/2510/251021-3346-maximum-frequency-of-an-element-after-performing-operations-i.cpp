class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        vector<int> cnt(100'000, 0);
        for (int &n: nums) {
            cnt[n - 1]++;
        }

        int s = 0;
        for (int i = 0; i < min((int)cnt.size(), k + 1); i++) {
            s += cnt[i];
        }
        int ans = cnt[0] + min(numOperations, s - cnt[0]);
        for (int i = 1; i < cnt.size(); i++) {
            if (i + k < cnt.size()) {
                s += cnt[i + k];
            }
            if (i - (k + 1) >= 0) {
                s -= cnt[i - (k + 1)];
            }

            ans = max(ans, cnt[i] + min(numOperations, s - cnt[i]));
        }
        return ans;
    }
};
