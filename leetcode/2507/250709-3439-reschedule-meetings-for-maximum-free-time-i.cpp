class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        const int n = startTime.size();

        vector<int> frees;
        frees.push_back(startTime[0]);
        for (int i = 1; i < n; i++) {
            frees.push_back(startTime[i] - endTime[i - 1]);
        }
        frees.push_back(eventTime - endTime[n - 1]);

        k++;
        int tsum = 0;
        for (int i = 0; i < k; i++) {
            tsum += frees[i];
        }

        int ans = tsum;
        for (int lp = 0; lp + k < frees.size(); lp++) {
            tsum -= frees[lp];
            tsum += frees[lp + k];

            ans = max(ans, tsum);
        }
        return ans;
    }
};
