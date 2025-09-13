class Solution {
public:
    int maxFreqSum(string s) {
        int cnts[26] = { 0 };
        for (auto &c: s) {
            cnts[c - 'a']++;
        }

        int vowel_max = 0, conso_max = 0;
        for (int i = 0, mask = 0x104111; i < 26; i++, mask >>= 1) {
            if (mask & 1) {
                vowel_max = max(vowel_max, cnts[i]);
            } else {
                conso_max = max(conso_max, cnts[i]);
            }
        }
        return vowel_max + conso_max;
    }
};
