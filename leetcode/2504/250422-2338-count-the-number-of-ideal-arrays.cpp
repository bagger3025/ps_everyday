class Solution {
    const int MOD = 1'000'000'000 + 7;

    vector<long long> fact;

    void getPrimeDivisors(int n, vector<int> &ret) {
        for (int p = 2; p <= n; p++) {
            int cnt = 0;
            while (n % p == 0) {
                cnt++;
                n /= p;
            }
            if (cnt > 0) {
                ret.push_back(cnt);
            }
        }
    }

    int modinv(int a) {
        return a <= 1 ? a : MOD - (static_cast<long long>(MOD / a) * modinv(MOD % a)) % MOD;
    }

    long long nCr(int n, int r) {
        return ((fact[n] * modinv(fact[r])) % MOD * modinv(fact[n - r])) % MOD;
    }

    long long nHr(int n, int r) {
        return nCr(n + r - 1, r);
    }

    int getValue(const vector<int> &divisors, int n) {
        long long ans = 1;
        for (auto &cnt: divisors) {
            ans = (ans * nHr(n, cnt)) % MOD;
        }
        return ans;
    }
public:
    Solution(): fact(10100) {
        fact[0] = 1;
        for (int i = 1; i < 10100; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }
    }

    int idealArrays(int n, int maxValue) {
        vector<vector<int>> divisors(maxValue + 1);
        for (int i = 2; i <= maxValue; i++) {
            getPrimeDivisors(i, divisors[i]);
        }

        long long ans = 0;
        for (int i = 1; i <= maxValue; i++) {
            long long t = getValue(divisors[i], n);
            ans = (ans + t) % MOD;
        }

        return ans;
    }
};
