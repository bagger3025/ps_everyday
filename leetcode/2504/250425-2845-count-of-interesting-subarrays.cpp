class Solution {
    vector<int> getGap(const vector<int> &nums, const int &modulo, const int &k) {
        const int n = nums.size();
        int previdx = -1;
        vector<int> gap;
        for (int i = 0; i < n; i++) {
            if (nums[i] % modulo != k) continue;
            gap.push_back(i - 1 - previdx);
            previdx = i;
        }
        gap.push_back(n - 1 - previdx);
        return gap;
    }

    vector<int> getRightSum(const vector<int> &gap, const int &modulo) {
        const int n = gap.size();
        vector<int> ret(n);
        for (int i = n - 1; i >= 0; i--) {
            ret[i] = i + modulo >= n ? gap[i] + 1 : gap[i] + ret[i + modulo] + 1;
        }
        return ret;
    }

public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        vector<int> gap = getGap(nums, modulo, k);
        vector<int> rightSum = getRightSum(gap, modulo);
        long long ans = 0;
        if (k == 0) {
            for (int i = 0; i < modulo && i < rightSum.size(); i++) {
                ans += static_cast<long long>(rightSum[i]) * (rightSum[i] - 1) / 2;
            }
        } else {
            for (int i = 0; i + k < rightSum.size(); i++) {
                ans += static_cast<long long>(gap[i] + 1) * rightSum[i + k];
            }
        }
        return ans;
    }
};
