class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        const int n = power.size();

        sort(power.begin(), power.end());
        deque<pair<int, long long>> dq; dq.push_front({-100, 0});
        long long dpval = power[0];

        for (int p = 1; p < n; p++) {
            if (power[p - 1] == power[p]) {
                dpval += power[p];
            } else {
                if (dq.back().second < dpval) {
                    // cout << "push back {" << power[p - 1] << ", " << dpval << "}" << endl;
                    dq.push_back({power[p - 1], dpval});
                }
                auto t = dq.front();
                while (t.first < power[p] - 2) {
                    dpval = t.second;
                    dq.pop_front();
                    if (dq.empty()) break;
                    t = dq.front();
                }
                dq.push_front({-100, dpval});

                dpval += power[p];
            }
        }

        while (!dq.empty()) {
            auto t = dq.front(); dq.pop_front();
            dpval = max(dpval, t.second);
        }
        return dpval;
    }
};
