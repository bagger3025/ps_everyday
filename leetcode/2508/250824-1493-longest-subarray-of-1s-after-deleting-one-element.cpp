class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int zeros = 0;
        int ret = 0;

        int temp_sum = 0;
        for (int lp = 0, rp = 0; rp < nums.size(); lp++) {
            while (rp < nums.size() && zeros < 2) {
                temp_sum += nums[rp];
                zeros += nums[rp] == 0;
                rp++;
            }
            ret = max(ret, temp_sum);
            if (nums[lp] == 0) zeros--;
            else temp_sum--;
        }
        if (ret == nums.size()) return ret - 1;
        return ret;
    }
};
