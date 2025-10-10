class Solution {
    int simulate(vector<int> &energy, int start, int k) {
        int val = 0, ans = energy[start];
        while (start >= 0) {
            val += energy[start]; ans = max(ans, val);
            start -= k;
        }
        return ans;
    }
public:
    int maximumEnergy(vector<int>& energy, int k) {
        const int n = energy.size();

        int ans = energy.back();
        for (int i = 0; i < k; i++) {
            int t = simulate(energy, n - 1 - i, k);
            ans = max(ans, t);
        }
        return ans;
    }
};
