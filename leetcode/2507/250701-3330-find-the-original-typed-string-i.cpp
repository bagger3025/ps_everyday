class Solution {
public:
    int possibleStringCount(string word) {
        char c = word[0]; int cnt = 1;
        int ans = 0;
        for (int i = 1; i < word.size(); i++) {
            char w = word[i];
            if (c == w) {
                cnt++;
            } else {
                ans += cnt - 1; cnt = 1; c = w;
            }
        }
        return ans + cnt;
    }
};
