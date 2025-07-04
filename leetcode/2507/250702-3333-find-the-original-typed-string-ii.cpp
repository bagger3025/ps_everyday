class Solution {
    struct dp_ele {
        char c;
        int count;
    };

    const int MOD = 1e9 + 7;

    vector<dp_ele> make_word_ele(const string &word, int &k) {
        const int n = word.size();
        vector<dp_ele> ret;

        dp_ele ele = {.c=word[0], .count=0};
        for (int i = 1; i < n; i++) {
            if (word[i] == word[i - 1]) {
                ele.count++;
            } else {
                k--;
                if (ele.count > 0)
                    ret.push_back(ele);
                ele = {.c=word[i], .count=0};
            }
        }
        if (ele.count > 0)
            ret.push_back(ele);
        k--;
        return ret;
    }

    int getAllPossible(const vector<dp_ele> &word_ele) {
        long long ret = 1;

        for (auto &e: word_ele){
            ret = (ret * (e.count + 1)) % MOD;
        }

        return ret;
    }
public:
    int possibleStringCount(string word, int k) {
        vector<dp_ele> word_ele = make_word_ele(word, k);

        if (word_ele.size() == 0) {
            return k <= 0;
        }

        if (k <= 0) {
            return getAllPossible(word_ele);
        }

        vector<vector<long long>> dp(2, vector<long long>(k));
        for (int i = 0; i < k; i++) {
            if (i <= word_ele[0].count) {
                dp[0][i] = 1;
            } else {
                dp[0][i] = 0;
            }
        }

        for (int i = 1; i < word_ele.size(); i++) {
            vector<long long> &cur_dp = dp[i % 2];
            vector<long long> &prev_dp = dp[1 ^ (i % 2)];
            cur_dp[0] = prev_dp[0];
            for (int rp = 1; rp < k; rp++) {
                cur_dp[rp] = cur_dp[rp - 1] + prev_dp[rp];
                if (rp > word_ele[i].count) {
                    cur_dp[rp] += MOD - prev_dp[rp - word_ele[i].count - 1];
                }
                cur_dp[rp] %= MOD;
            }
        }

        long long rest = 0;
        vector<long long> &cur_dp = dp[1 ^ (word_ele.size() % 2)];
        for (int i = 0; i < k; i++) {
            rest = (rest + cur_dp[i]) % MOD;
        }

        return ((long long)getAllPossible(word_ele) + MOD - rest) % MOD;
    }
};

