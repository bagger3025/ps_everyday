class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        vector<int> cnt(100, 0);
        for (const int &n: nums) {
            cnt[n - 1]++;
        }
        int maxval = cnt[0], maxcnt = 1;
        for (int i = 1; i < cnt.size(); i++) {
            if (cnt[i] == maxval) maxcnt++;
            else if (cnt[i] > maxval) {
                maxval = cnt[i]; maxcnt = 1;
            }
        }
        return maxval * maxcnt;
    }
};
