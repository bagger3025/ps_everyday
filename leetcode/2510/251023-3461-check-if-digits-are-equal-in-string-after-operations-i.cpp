class Solution {
public:
    bool hasSameDigits(string s) {
        vector<int> v;
        for (auto &c: s) {
            v.push_back(c - '0');
        }
        for (int i = v.size(); i > 2; i--) {
            for (int j = 1; j < i; j++) {
                v[j - 1] = (v[j - 1] + v[j]) % 10;
            }
        }

        return v[0] == v[1];
    }
};
