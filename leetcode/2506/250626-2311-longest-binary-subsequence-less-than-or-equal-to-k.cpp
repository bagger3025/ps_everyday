class Solution {
    string getBinary(int k) {
        string ret;

        while (k > 0) {
            ret += '0' + k % 2;
            k /= 2;
        }
        return ret;
    }

    vector<int> getOneList(const string &s) {
        vector<int> ret;

        for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] == '1') ret.push_back(i);
        }
        return ret;
    }

    int matching(const string &s, const string &binaryK, const vector<int> &oneList) {
        int onep = 0;

        int sp = s.size() - 1, bp = 0;
        while (sp >= 0 && bp < binaryK.size()) {
            if (s[sp] == binaryK[bp]) {
                bp++;
                if (onep != oneList.size() && oneList[onep] < bp) onep++;
            }

            if (bp == binaryK.size()) break;
            if (s[sp] == '1') {
                sp--; continue;
            }

            while (onep != oneList.size()) {
                int bonep = oneList[onep];
                if (s.size() - sp < bonep + 1) break;
                bp = bonep + 1;
                onep++;
            }

            sp--;
        }

        return sp;
    }

    int getLongest(const string &s, const int idx, int kSize) {
        int zeros = 0;
        for (int i = 0; i < idx; i++) {
            zeros += s[i] == '0';
        }

        int ans = zeros + kSize;
        if (idx < 0) ans = kSize - 1;

        for (int i = idx + 1; i < s.size(); i++) {
            if (s[i] == '0') {
                zeros++;
            } else {
                ans = max(ans, zeros + min(kSize - 1, (int)s.size() - i));
            }
        }
        ans = max(ans, zeros);

        return ans;
    }
public:
    int longestSubsequence(string s, int k) {
        string binaryK = getBinary(k);
        if (s.size() < binaryK.size()) return s.size();

        vector<int> oneList = getOneList(binaryK);
        int idx = matching(s, binaryK, oneList);
        return getLongest(s, idx, binaryK.size());
    }
};
