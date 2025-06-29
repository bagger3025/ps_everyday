class Solution {
    const int MOD = 1'000'000'000 + 7;

    long long modpow(int a, int p) {
        if (p == 0) return 1;
        if (p == 1) return a;

        long long r = modpow(a, p / 2);
        if (p % 2) return (r * r * a) % MOD;
        else return (r * r) % MOD;
    }

public:
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        const int n = nums.size();
        vector<long long> pow2(n + 1);
        pow2[0] = 1;
        for (int i = 1; i <= n; i++) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        int rp = n - 1;
        long long ans = 0;
        for (int lp = 0; lp <= rp; lp++) {
            while (rp >= lp && nums[lp] + nums[rp] > target) rp--;
            if (rp < lp) break;

            int cnt = 1;
            while (lp + cnt < n && nums[lp] == nums[lp + cnt]) cnt++;

            ans += pow2[rp - lp - cnt + 1] * (pow2[cnt] - 1);
            ans %= MOD;

            lp += cnt - 1;
        }

        return ans;
    }
};
