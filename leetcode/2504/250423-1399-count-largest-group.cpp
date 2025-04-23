class Solution {
    int getDigitSum(int n) {
        int ans = 0;
        while (n > 0) {
            ans += n % 10;
            n /= 10;
        }
        return ans;
    }
public:
    int countLargestGroup(int n) {
        vector<int> groups(37, 0);
        for (int i = 1; i <= n; i++) {
            int digitSum = getDigitSum(i);
            groups[digitSum]++;
        }

        int maxval = groups[0];
        int maxcnt = 1;
        for (int i = 1; i < 37; i++) {
            if (groups[i] > maxval) {
                maxval = groups[i]; maxcnt = 1;
            } else if (groups[i] == maxval) {
                maxcnt++;
            }
        }
        return maxcnt;
    }
};
