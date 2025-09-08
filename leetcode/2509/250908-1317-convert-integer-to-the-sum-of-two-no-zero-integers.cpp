class Solution {
    bool isValid(int n) {
        while (n > 0) {
            if (n % 10 == 0) return false;
            n /= 10;
        }
        return true;
    }
public:
    vector<int> getNoZeroIntegers(int n) {
        for (int i = 1; i < n; i++) {
            if (!isValid(i) || !isValid(n - i)) continue;
            return {i, n - i};
        }
        return {};
    }
};
