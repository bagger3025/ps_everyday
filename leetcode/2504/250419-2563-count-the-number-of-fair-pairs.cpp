class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());

        int lp = nums.size() - 1, rp = nums.size() - 1;
        long long ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            while (lp > i && nums[i] + nums[lp] >= lower) lp--;
            while (rp > i && nums[i] + nums[rp] > upper) rp--;
            if (rp <= i) break;
            lp = max(lp, i);
            ans += rp - lp;
        }
        return ans;
    }
};
