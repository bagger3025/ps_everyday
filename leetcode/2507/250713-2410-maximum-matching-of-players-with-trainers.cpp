class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(trainers.begin(), trainers.end());
        sort(players.begin(), players.end());
        int ans = 0;
        for (int i = 0, tp = 0; i < players.size(); i++) {
            while (tp < trainers.size() && players[i] > trainers[tp]) {
                tp++;
            }
            if (tp != trainers.size()) {ans++; tp++;}
            else break;
        }
        return ans;
    }
};
