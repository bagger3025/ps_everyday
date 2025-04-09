class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        vector<bool> flag(101, false);
        
        int ans = 0;
        for (int &n: nums) {
            if (n < k) return -1;
            if (n == k) continue;
            if (!flag[n]) ans++;
            flag[n] = true;
        }
        
        return ans;
    }
};
