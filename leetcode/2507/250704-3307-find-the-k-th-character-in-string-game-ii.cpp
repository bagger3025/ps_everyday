class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        if (k == 1) return 'a';
        k--;
        vector<int> bits;
        while (k > 0) {
            bits.push_back(k % 2);
            k /= 2;
        }
        int ans = 0;
        for (int i = bits.size() - 1; i >= 0; i--) {
            ans += operations[i] && bits[i];
        }
        return 'a' + ans % 26;
    }
};
