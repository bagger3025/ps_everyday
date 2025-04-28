class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        const int n = nums.size();

        long long s = 0, ans = 0;
        for (int lp = 0, rp = 0; rp < n; rp++) {
            s += nums[rp];
            while (lp <= rp && s > (k - 1) / (rp - lp + 1)) {
                s -= nums[lp]; lp++;
            }
            ans += rp - lp + 1;
        }
        return ans;
    }
};
