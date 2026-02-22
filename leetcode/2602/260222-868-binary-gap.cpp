class Solution {
public:
    int binaryGap(int n) {
        while (n % 2 == 0) {
            n /= 2;
        }

        int ret = 0;
        while (n % 2 == 1) {
            n >>= 1;
            if (n == 0) return ret;
            int t = 1;
            while (n % 2 != 1) {
                n >>= 1; t++;
            }
            ret = max(ret, t);
        }
        return ret;
    }
};
