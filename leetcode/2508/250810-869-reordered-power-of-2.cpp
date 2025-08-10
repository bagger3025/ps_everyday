class Solution {
public:
    bool reorderedPowerOf2(int n) {
        int cnt[10] = { 0 }, n_digits = 0;
        while (n > 0) {
            cnt[n % 10]++; n /= 10; n_digits++;
        }
        if (n_digits == 10) return false;

        int n_tens = 1;
        for (int i = 0; i < n_digits - 1; i++) {
            n_tens *= 10;
        }

        for (int i = 0; i < 31; i++) {
            int val = 1 << i;
            if (val < n_tens) continue;
            if (val > n_tens * 10) break;

            int binary_cnts[10] = { 0 };
            while (val > 0) {
                binary_cnts[val % 10]++; val /= 10;
            }
            bool ret = true;
            for (int j = 0; j < 10; j++) {
                if (cnt[j] != binary_cnts[j]) {
                    ret = false; break;
                }
            }
            if (ret) return true;
        }

        return false;
    }
};
