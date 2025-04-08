class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        vector<bool> visited(100, false);
        int i;
        for (i = nums.size() - 1; i >= 0; i--) {
            const int &n = nums[i];
            if (visited[n - 1]) break;
            visited[n - 1] = true;
        }
        
        i++;
        return i / 3 + ((i % 3) ? 1 : 0); 
    }
};
