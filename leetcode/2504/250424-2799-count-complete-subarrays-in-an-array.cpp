class Solution {
    int getDistinctCnt(const vector<int> &nums) {
        vector<bool> arr(2000, false);
        int ans = 0;
        for (const int &n: nums) {
            ans += !arr[n - 1];
            arr[n - 1] = true;
        }
        return ans;
    }
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int lp = 0, rp = 0;
        const int n = nums.size();
        const int distinctCnt = getDistinctCnt(nums);
        vector<int> cntArr(2000, 0);
        int localDistinct = 0;
        int ans = 0;

        while (lp < n) {
            while (rp < n && localDistinct != distinctCnt) {
                const int &n = nums[rp++];
                int &cnt = cntArr[n - 1];
                localDistinct += cnt == 0;
                cnt++;
            }

            if (localDistinct != distinctCnt) break;

            while (localDistinct == distinctCnt) {
                ans += n - rp + 1;
                const int &n = nums[lp++];
                int &cnt = cntArr[n - 1];
                localDistinct -= cnt == 1;
                cnt--;
            }
        }
        return ans;
    }
};
