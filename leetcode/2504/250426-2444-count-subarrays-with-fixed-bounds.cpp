class Solution {
    static const int MIN_VAL = 0, MAX_VAL = 1, OUT_VAL = 2;

    vector<int> getOutIdxes(const vector<int> &nums, const int &minK, const int &maxK) {
        const int n = nums.size();

        vector<int> ret;
        for (int i = 0; i < n; i++) {
            if (nums[i] < minK || nums[i] > maxK) ret.push_back(i);
        }
        return ret;
    }

    bool conditionMet(const int cnt[]) {
        return cnt[MIN_VAL] > 0 && cnt[MAX_VAL] > 0;
    }

    void updateCnt(const int &n, int cnt[], const int &minK, const int &maxK) {
        if (n == minK) cnt[MIN_VAL]++;
        if (n == maxK) cnt[MAX_VAL]++;
        if (n < minK || n > maxK) cnt[OUT_VAL]++;
    }

    void deleteCnt(const int &n, int cnt[], const int &minK, const int &maxK) {
        if (n == minK) cnt[MIN_VAL]--;
        if (n == maxK) cnt[MAX_VAL]--;
    }

public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        const int n = nums.size();

        vector<int> outIdx = getOutIdxes(nums, minK, maxK);
        int lp = 0, rp = 0, outp = 0;
        int cnt[3] = { 0 };

        long long ans = 0;
        while (rp < n) {
            while (rp < n && !conditionMet(cnt)) {
                updateCnt(nums[rp], cnt, minK, maxK);
                rp++;
                if (cnt[OUT_VAL] > 0) {
                    outp++;
                    cnt[0] = cnt[1] = cnt[2] = 0;
                    lp = rp;
                }
            }

            int closestOutIdx = outp >= outIdx.size() ? n : outIdx[outp];

            while (lp < rp && conditionMet(cnt)) {
                ans += closestOutIdx - rp + 1;
                deleteCnt(nums[lp], cnt, minK, maxK);
                lp++;
            }
        }
        return ans;
    }
};
