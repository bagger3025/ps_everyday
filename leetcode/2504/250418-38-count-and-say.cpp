class Solution {
    string nextSay(const string &s) {
        string ret;
        int previdx = 0;
        for (int i = 0; i <= s.size(); i++) {
            if (i == s.size() || s[i] != s[previdx]) {
                ret += '0' + (i - previdx);
                ret += s[previdx];
                previdx = i;
            }
        }
        return ret;
    }
public:
    string countAndSay(int n) {
        string s = "1";
        for (int i = 1; i < n; i++) {
            s = nextSay(s);
        }
        return s;
    }
};
