class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        const int MAX = 100'000;
        bool cnt[MAX + 1] = { false };
        for (const auto &n: nums) {
            cnt[n] = true;
        }

        int ans = 0;
        for (int i = 0; i <= MAX; i++) {
            if (!cnt[i]) continue;
            ans++;
            i += k;
        }
        return ans;
    }
};
