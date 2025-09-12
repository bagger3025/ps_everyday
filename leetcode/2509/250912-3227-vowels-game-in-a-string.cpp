class Solution {
    bool is_vowel(const char &ch) {
        return (0x104111 >> (ch - 97)) & 1;
    }
public:
    bool doesAliceWin(string s) {
        int vowel_cnt = 0;
        for (auto &c: s) {
            if (is_vowel(c)) {
                vowel_cnt++;
            }
        }

        return vowel_cnt != 0;
    }
};
