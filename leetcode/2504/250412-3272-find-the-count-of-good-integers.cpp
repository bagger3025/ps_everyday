class Solution {
    long long int_pow(int a, int p) {
        if (p == 0) return 1;
        if (p == 1) return a;

        long long t = int_pow(a, p / 2);
        if (p % 2) {
            return t * t * a;
        } else {
            return t * t;
        }
    }

    int recInteger(int val, int digit) {
        int arr[10], arridx = 0;
        while (val > 0) {
            arr[arridx++] = val % 10;
            val /= 10;
        }
        int ret = 0;
        for (int i = arridx - digit; i < arridx; i++) {
            ret = ret * 10 + arr[i];
        }
        return ret;
    }

    long long toCanonical(long long val) {
        int cnt[10] = { 0 };
        while (val > 0) {
            cnt[val % 10]++;
            val /= 10;
        }
        long long ret = 0;
        for (int i = 9; i >= 0; i--) {
            for (int j = 0; j < cnt[i]; j++) {
                ret = ret * 10 + i;
            }
        }
        return ret;
    }

    void fillCnt(int cnt[], long long val) {
        while (val > 0) {
            cnt[val % 10]++;
            val /= 10;
        }
    }

    long long getCombination(int cnt[], const int n, const long long factorial[]) {
        long long t = factorial[n];
        for (int i = 0; i < 10; i++) {
            t /= factorial[cnt[i]];
        }
        return t;
    }
public:
    long long countGoodIntegers(int n, int k) {
        int cnt[10] = { 0 };

        long long from = int_pow(10, n / 2 + n % 2 - 1);

        long long i_pow = int_pow(10, n / 2);
        unordered_set<long long> long_cnts;
        for (long long i = from; i < from * 10; i++) {
            long long val = i * i_pow + recInteger(i, n / 2);
            if (val % k != 0) continue;
            long_cnts.insert(toCanonical(val));
        }

        int ans = 0;
        long long factorial[11];
        factorial[0] = 1;
        factorial[1] = 1;
        for (int i = 2; i <= 10; i++) {
            factorial[i] = factorial[i - 1] * i;
        }

        for (auto it = long_cnts.begin(); it != long_cnts.end(); it++) {
            int cnt[10] = { 0 };
            fillCnt(cnt, *it);

            long long t = getCombination(cnt, n, factorial);
            if (cnt[0] > 0) {
                cnt[0]--;
                t -= getCombination(cnt, n - 1, factorial);
            }
            
            ans += t;
        }

        return ans;
    }
};
