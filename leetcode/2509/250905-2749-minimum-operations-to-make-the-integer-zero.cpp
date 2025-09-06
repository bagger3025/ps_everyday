class Solution {
    int countBits(long long n) {
        int cnt = 0;
        while (n > 0) {
            cnt += n % 2; n /= 2;
        }
        return cnt;
    }

public:
    int makeTheIntegerZero(int num1, int num2) {
        long long n1 = num1;
        for (int i = 0; n1 > num2; i++) {
            n1 -= num2;
            int bits = countBits(n1);
            if (bits <= i + 1 && n1 >= i + 1) return i + 1;
        }
        return -1;
    }
};
