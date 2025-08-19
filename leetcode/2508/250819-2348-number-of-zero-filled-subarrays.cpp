class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long ans = 0;
        long long sublen = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                sublen = 0; continue;
            }
            sublen++;
            ans += sublen;
        }
        return ans;
    }
};
