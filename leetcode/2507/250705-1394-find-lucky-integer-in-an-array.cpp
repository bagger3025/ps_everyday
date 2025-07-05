class Solution {
public:
    int findLucky(vector<int>& arr) {
        int cnt[500] = { 0 };
        int maxval = -1;
        for (const int &a: arr) {
            cnt[a - 1]++;
            maxval = max(maxval, cnt[a - 1]);
        }
        for (int i = maxval - 1; i >= 0; i--) {
            if (cnt[i] == i + 1) return i + 1;
        }
        return -1;
    }
};
