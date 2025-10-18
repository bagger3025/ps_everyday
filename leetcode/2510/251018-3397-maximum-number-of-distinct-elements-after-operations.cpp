class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        const int n = nums.size();
        sort(nums.begin(), nums.end());
        
        int maxnum = nums[n - 1] + k + 1;
        int ret = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (maxnum > nums[i] + k) {
                maxnum = nums[i] + k - 1;
                ret++;
            } else if (maxnum >= nums[i] - k) {
                maxnum--; ret++;
            }
        }
        return ret;
    }
};
