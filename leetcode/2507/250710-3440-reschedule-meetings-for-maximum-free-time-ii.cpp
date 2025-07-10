class Solution {
    bool canMoveAway(const vector<pair<int, int>> &v, int idx, int event_length) {
        const int n = v.size();
        for (int i = 0; i < n; i++) {
            if (v[i].second == idx || v[i].second == idx + 1) continue;
            if (v[i].first < event_length) return false;
            return true;
        }
        return false;
    }
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        const int n = startTime.size();
        vector<int> frees; frees.reserve(n + 1);
        
        frees.push_back(startTime[0]);
        for (int i = 1; i < n; i++) {
            frees.push_back(startTime[i] - endTime[i - 1]);
        }
        frees.push_back(eventTime - endTime[n - 1]);

        vector<pair<int, int>> frees_max;
        for (int i = 0; i < 3; i++) {
            int free_idx = -1;
            for (int j = 0; j <= n; j++) {
                if (frees[j] <= 0) continue;
                if (free_idx == -1 || frees[j] > frees[free_idx]) {
                    free_idx = j;
                }
            }
            if (free_idx == -1) break;
            frees_max.push_back({frees[free_idx], free_idx});
            frees[free_idx] = -1;
        }

        for (int i = 0; i < frees_max.size(); i++) {
            frees[frees_max[i].second] = frees_max[i].first;
        }

        int ans = -1;
        for (int i = 0; i < n; i++) {
            int events = endTime[i] - startTime[i];
            if (canMoveAway(frees_max, i, events)) {
                ans = max(ans, frees[i] + events + frees[i + 1]);
            } else {
                ans = max(ans, frees[i] + frees[i + 1]);
            }
        }

        return ans;
    }
};
