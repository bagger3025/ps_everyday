class Solution {
    const int UNDEF = -1;

    typedef vector<vector<vector<int>>> vvvi;

    int getMin(const int n, const int firstPlayer, const int secondPlayer, int lvl, vvvi &dp) {
        if (n == 2) return 1;

        int &curcell = dp[lvl][firstPlayer][secondPlayer];
        if (curcell != UNDEF) return curcell;
        if (firstPlayer + secondPlayer == n - 1) return curcell = 1;

        int l_player = 0, r_player = 0, r_saved = 0;
        int nextFirstPlayer = firstPlayer, nextSecondPlayer = secondPlayer;
        for (int i = 0; i < n / 2; i++) {
            int other_i = n - 1 - i;

            if (i == firstPlayer || i == secondPlayer) {
                if (firstPlayer > other_i) nextFirstPlayer--;
                if (secondPlayer > other_i) nextSecondPlayer--;
                continue;
            } else if (other_i == firstPlayer || other_i == secondPlayer) {
                if (firstPlayer > i) nextFirstPlayer--;
                if (secondPlayer > i) nextSecondPlayer--;
                continue;
            }

            bool l_increased = false, r_increased = false;

            if (firstPlayer >= other_i) {
                nextFirstPlayer--;
            } else {
                if (firstPlayer > i) {
                    l_increased = true;
                    l_player++;
                }
            }

            if (secondPlayer >= other_i) {
                nextSecondPlayer--;
                if (l_increased) r_saved++;
            } else {
                if (secondPlayer > i && !l_increased) {
                    r_player++;
                }
            }
        }

        const int next_n = n - n / 2;
        int minval = n;
        for (int i = 0; i <= l_player; i++) {
            for (int j = max(i - r_saved, 0); j <= r_player + min(l_player - r_saved, i); j++) {
                int cand = getMin(next_n, nextFirstPlayer - i, nextSecondPlayer - j, lvl + 1, dp);
                minval = min(minval, cand);
            }
        }
        return curcell = minval + 1;
    }

    int getMax(const int n, const int firstPlayer, const int secondPlayer, int lvl, vvvi &dp) {
        if (n == 2) return 1;

        int &curcell = dp[lvl][firstPlayer][secondPlayer];
        if (curcell != UNDEF) return curcell;
        if (firstPlayer + secondPlayer == n - 1) return curcell = 1;

        int l_player = 0, r_player = 0, r_saved = 0;
        int nextFirstPlayer = firstPlayer, nextSecondPlayer = secondPlayer;
        for (int i = 0; i < n / 2; i++) {
            int other_i = n - 1 - i;

            if (i == firstPlayer || i == secondPlayer) {
                if (firstPlayer > other_i) nextFirstPlayer--;
                if (secondPlayer > other_i) nextSecondPlayer--;
                continue;
            } else if (other_i == firstPlayer || other_i == secondPlayer) {
                if (firstPlayer > i) nextFirstPlayer--;
                if (secondPlayer > i) nextSecondPlayer--;
                continue;
            }

            bool l_increased = false, r_increased = false;

            if (firstPlayer >= other_i) {
                nextFirstPlayer--;
            } else {
                if (firstPlayer > i) {
                    l_increased = true;
                    l_player++;
                }
            }

            if (secondPlayer >= other_i) {
                nextSecondPlayer--;
                if (l_increased) r_saved++;
            } else {
                if (secondPlayer > i && !l_increased) {
                    r_player++;
                }
            }
        }

        const int next_n = n - n / 2;
        int maxval = -1;
        int r_target = r_saved > 0 ? l_player - r_saved : r_player;
        for (int i = 0; i <= l_player; i++) {
            for (int j = max(i - r_saved, 0); j <= r_player + min(l_player - r_saved, i); j++) {
                int cand = getMax(next_n, nextFirstPlayer - i, nextSecondPlayer - j, lvl + 1, dp);
                maxval = max(maxval, cand);
            }
        }
        return curcell = maxval + 1;
    }

public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        firstPlayer--; secondPlayer--;
        vector<vector<vector<int>>> mindp(5), maxdp(5);
        for (int t = n, i = 0; t > 2; t -= t / 2, i++) {
            mindp[i] = vector<vector<int>>(t, vector<int>(t, UNDEF));
            maxdp[i] = vector<vector<int>>(t, vector<int>(t, UNDEF));
        }
        int minval = getMin(n, firstPlayer, secondPlayer, 0, mindp);
        int maxval = getMax(n, firstPlayer, secondPlayer, 0, maxdp);
        return {minval, maxval};
    }
};
