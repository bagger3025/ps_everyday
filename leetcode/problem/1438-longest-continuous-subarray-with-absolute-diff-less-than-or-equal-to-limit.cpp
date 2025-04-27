class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        const int n = nums.size();
        int ans = 1;

        deque<int> maxq, minq;
        for (int lp = 0, rp = 0; rp < n; rp++) {
            while (!maxq.empty() && nums[maxq.back()] < nums[rp]) maxq.pop_back();
            maxq.push_back(rp);
            while (!minq.empty() && nums[minq.back()] > nums[rp]) minq.pop_back();
            minq.push_back(rp);

            while (nums[maxq.front()] - nums[minq.front()] > limit) {
                if (maxq.front() == lp) maxq.pop_front();
                if (minq.front() == lp) minq.pop_front();
                lp++;
            }
            ans = max(ans, rp - lp + 1);
        }
        return ans;
    }
};
