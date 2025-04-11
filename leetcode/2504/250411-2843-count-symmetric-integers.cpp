class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        int ans = 0;
        for (int i = 11; i <= 99; i += 11) {
            if (low <= i && i <= high) ans++;
        }

        for (int i = max(10, low / 100); i <= min(99, high / 100); i++) {
            int i_sum = i / 10 + i % 10;

            // smallest two digit number that sums to `i_sum`
            int low_digits = i_sum <= 9 ? i_sum : (i_sum - 9) * 10 + 9;
            int loop_cnt = i_sum <= 9 ? i_sum + 1 : 19 - i_sum;
            int target = i * 100 + low_digits;

            for (int j = 0; j < loop_cnt; j++, target += 9) {
                if (target > high) break;
                if (low <= target) ans++;
            }
        }
        return ans;
    }
};
