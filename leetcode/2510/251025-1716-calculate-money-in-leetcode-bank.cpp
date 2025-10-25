class Solution {
public:
    int totalMoney(int n) {
        int ans = 0;
        int start = 1;
        while (n >= 7) {
            ans += 21 + start * 7;
            n -= 7; start++;
        }
        for (int i = 0; i < n; i++) {
            ans += start; start++;
        }
        return ans;
    }
};
