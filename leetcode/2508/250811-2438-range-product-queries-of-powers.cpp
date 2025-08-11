class Solution {
    int MOD = 1'000'000'000 + 7;

    long long powmod(int a, int p) {
        if (p == 0) return 1;
        if (p == 1) return a;

        long long t = powmod(a, p / 2);
        t = (t * t) % MOD;
        if (p % 2) {
            return (t * a) % MOD;
        } else {
            return t;
        }
    }
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> arr;
        for (int i = 0; i < 31 && n > 0; i++) {
            if ((1 << i) & n) {
                arr.push_back(i);
                n -= (1 << i);
            }
        }

        for (int i = 1; i < arr.size(); i++) {
            arr[i] += arr[i - 1];
        }

        vector<int> ans;

        for (auto &q: queries) {
            if (q[0] >= arr.size()) {
                ans.push_back(0);
                continue;
            }

            int leftend = q[0] > 0 ? arr[q[0] - 1] : 0;
            int rightend = q[1] < arr.size() ? arr[q[1]] : arr[arr.size() - 1];

            int k = rightend - leftend;
            ans.push_back(powmod(2, k));
        }

        return ans;
    }
};
