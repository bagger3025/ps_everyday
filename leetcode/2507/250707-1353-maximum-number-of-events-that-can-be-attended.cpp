class Solution {
    int getNextTime(vector<int> &times, int t) {
        if (t >= times.size()) return t;
        if (times[t] == t) return t;
        return times[t] = getNextTime(times, times[t]);
    }
public:
    int maxEvents(vector<vector<int>>& events) {
        vector<int> times(1e5);
        for (int i = 0; i < times.size(); i++) {
            times[i] = i;
        }

        vector<pair<int, int>> event_pair;
        for (auto &e: events) {
            event_pair.push_back({e[1] - 1, e[0] - 1});
        }
        sort(event_pair.begin(), event_pair.end());

        int ans = 0;
        for (int i = 0; i < event_pair.size(); i++) {
            const int &start = event_pair[i].second;
            const int &end = event_pair[i].first;

            int find_time = getNextTime(times, start);
            if (find_time <= end) {
                ans++; times[find_time] = find_time + 1;
            }
        }
        return ans;
    }
};
