class Solution {
    char to_lower(char c) {
        if ('A' <= c && c <= 'Z') return c - 'A' + 'a';
        return c;
    }

    bool is_vowel(char c) {        
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    bool is_alpha(char c) {
        return 'a' <= c && c <= 'z';
    }

    bool is_digit(char c) {
        return '0' <= c && c <= '9';
    }
public:
    bool isValid(string word) {
        if (word.size() < 3) return false;

        bool has_vowel = false, has_consonant = false;

        for (auto &c: word) {
            char lower_c = to_lower(c);
            if (is_vowel(lower_c)) has_vowel = true;
            else if (is_alpha(lower_c)) has_consonant = true;
            else if (!is_digit(lower_c)) return false;
        }

        return has_vowel && has_consonant;
    }
};
