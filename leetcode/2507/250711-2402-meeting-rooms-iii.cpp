bool compare(const vector<int> &a, const vector<int> &b) {
    return a[0] < b[0];
}

class Solution {
    struct pq_ele {
        int room;
        long long end_time;

        bool operator<(const pq_ele &other) const {
            if (this->end_time == other.end_time) return this->room > other.room;
            return this->end_time > other.end_time;
        }
    };


public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        const int tot_n = meetings.size();

        sort(meetings.begin(), meetings.end(), compare);

        priority_queue<int, vector<int>, greater<>> frees;
        for (int i = 0; i < n; i++) frees.push(i);

        vector<int> cnt(n, 0);
        priority_queue<pq_ele> on_meet;
        for (int midx = 0; midx < tot_n; midx++) {
            long long cur_time = meetings[midx][0];
            while (!on_meet.empty() && on_meet.top().end_time <= cur_time) {
                auto t = on_meet.top(); on_meet.pop();
                frees.push(t.room);
            }

            if (frees.empty()) {
                auto t = on_meet.top(); on_meet.pop();
                cur_time = t.end_time;
                frees.push(t.room);
            }

            auto t = frees.top(); frees.pop();

            int meeting_time = meetings[midx][1] - meetings[midx][0];
            cnt[t]++;
            on_meet.push({t, cur_time + meeting_time});
        }

        return max_element(cnt.begin(), cnt.end()) - cnt.begin();
    }
};
