class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        int last = -1;
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != key) continue;
            for (int j = max(last, i - k - 1) + 1; j <= min(i + k, (int)nums.size() - 1); j++) {
                ans.push_back(j);
            }
            last = i + k;
        }
        return ans;
    }
};
