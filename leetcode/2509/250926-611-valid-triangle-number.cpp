class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<int> cnt(1000 + 1, 0);
        for (auto &n: nums) {
            cnt[n]++;
        }
        for (int i = 1; i < cnt.size(); i++) {
            cnt[i] += cnt[i - 1];
        }

        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) continue;
            for (int j = i + 1, rp = j + 1; j < nums.size(); j++) {
                while (rp < nums.size() && nums[rp] < nums[i] + nums[j]) rp++;
                ans += rp - j - 1;
            }
        }
        return ans;
    }
};
