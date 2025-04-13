class Solution {
    static const int MOD = 1e9 + 7;
    long long int_pow(int a, long long p) {
        if (p == 0) return 1;
        if (p == 1) return a;

        long long t = int_pow(a, p / 2);
        t = (t * t) % MOD;
        if (p % 2) {
            return (t * a) % MOD;
        } else {
            return t;
        }
    }

public:
    int countGoodNumbers(long long n) {
        long long even_count = int_pow(5, n - n / 2);
        long long odd_count = int_pow(4, n / 2);
        return (even_count * odd_count) % MOD;
    }
};
