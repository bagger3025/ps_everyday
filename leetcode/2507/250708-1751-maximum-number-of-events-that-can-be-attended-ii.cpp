bool compare (const vector<int> &a, const vector<int> &b) {
    return a[1] < b[1];
}

class Solution {
    int get_max(const vector<int> &v) {
        int maxval = v[0];
        for (int i = 1; i < v.size(); i++) {
            maxval = max(maxval, v[i]);
        }
        return maxval;
    }

public:
    int maxValue(vector<vector<int>>& events, int k) {
        sort(events.begin(), events.end(), compare);

        map<int, vector<int>> dp;
        vector<int> cur(k, -1);
        for (auto &e: events) {
            auto it = dp.lower_bound(e[0]);            
            if (it == dp.begin()) {
                cur[0] = max(cur[0], e[2]);
            } else {
                it--;
                const vector<int> &prev = it->second;
                cur[0] = max(cur[0], e[2]);
                for (int i = 0; i < prev.size() - 1; i++) {
                    if (prev[i] == -1) break;
                    cur[i + 1] = max(cur[i + 1], prev[i] + e[2]);
                }
            }

            dp[e[1]] = cur;
        }

        return get_max((--dp.end())->second);
    }
};
