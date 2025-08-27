class Solution {
    enum Direction {
        UPRIGHT,
        UPLEFT,
        DOWNRIGHT,
        DOWNLEFT,
    };

    struct vector_ele {
        int one_turn[4] = { 0 };
        int two_turn[4] = { 0 };
    };

    typedef vector<int> vi;
    typedef vector<vi> vvi;

    typedef vector<vector_ele> ve;
    typedef vector<ve> vve;
    typedef vector<vve> vvve;

    void print_dp(const vve &dp) {
        for (auto &row: dp) {
            for (auto &cell: row) {
                cout << "{";
                for (int i = 0; i < 4; i++) {
                    cout << cell.one_turn[i] << " ";
                } cout << "} ";
                cout << "{";
                for (int i = 0; i < 4; i++) {
                    cout << cell.two_turn[i] << " ";
                } cout << "} | ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void set_one(vector_ele &e) {
        for (int i = 0; i < 4; i++) {
            e.one_turn[i] = 1;
            e.two_turn[i] = 1;
        }
    }

    void init_dp(vve &dp, vvi &grid) {
        const int n = grid.size(), m = grid[0].size();

        for (int i = 0; i < m; i++) {
            if (grid[0][i] != 1) {
                set_one(dp[0][i]);
            }
            if (grid[n - 1][i] != 1) {
                set_one(dp[n - 1][i]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (grid[i][0] != 1) {
                set_one(dp[i][0]);
            }
            if (grid[i][m - 1] != 1) {
                set_one(dp[i][m - 1]);
            }
        }
    }

    void one_turn_downleft(vve &dp, const vvi &grid, int row, int col) {
        const int &prevdp = dp[row][col].one_turn[UPRIGHT];
        for (
            int currow = row, curcol = col, i = 1;
            i <= prevdp;
            i++, currow--, curcol++
        ) {
            dp[currow][curcol].one_turn[DOWNLEFT] = i;
        }
    }

    void one_turn_downright(vve &dp, const vvi &grid, int row, int col) {
        const int &prevdp = dp[row][col].one_turn[UPLEFT];
        for (
            int currow = row, curcol = col, i = 1;
            i <= prevdp;
            i++, currow--, curcol--
        ) {
            dp[currow][curcol].one_turn[DOWNRIGHT] = i;
        }
    }

    void process_one_turn(vve &dp, const vvi &grid) {
        const int n = grid.size(), m = grid[0].size();

        // UPRIGHT
        for (int sum = 0; sum < n + m - 1; sum++) {
            int col = min(m - 1, sum);
            int row = sum - col;
            row++; col--;
            for (; row < n && col >= 0; row++, col--) {
                const int &prevval = grid[row - 1][col + 1];
                const int &gridval = grid[row][col];
                if (gridval == 1 || gridval != 2 - prevval) {
                    one_turn_downleft(dp, grid, row - 1, col + 1);
                    if (gridval != 1) {
                        dp[row][col].one_turn[UPRIGHT] = 1;
                    }
                } else {
                    dp[row][col].one_turn[UPRIGHT] = dp[row - 1][col + 1].one_turn[UPRIGHT] + 1;
                }
            }
            one_turn_downleft(dp, grid, row - 1, col + 1);
        }

        // UPLEFT
        for (int diff = 0; diff < n + m - 1; diff++) {
            int col = max(diff - n + 1, 0);
            int row = n - 1 - diff + col;
            row++; col++;
            for (; row < n && col < m; row++, col++) {
                const int &prevval = grid[row - 1][col - 1];
                const int &gridval = grid[row][col];
                if (gridval == 1 || gridval != 2 - prevval) {
                    one_turn_downright(dp, grid, row - 1, col - 1);
                    if (gridval != 1) dp[row][col].one_turn[UPLEFT] = 1;
                } else {
                    dp[row][col].one_turn[UPLEFT] = dp[row - 1][col - 1].one_turn[UPLEFT] + 1;
                }
            }
            one_turn_downright(dp, grid, row - 1, col - 1);
        }
    }

    void process_two_turn(vve &dp, const vvi &grid) {
        const int n = grid.size(), m = grid[0].size();

        for (int sum = 0; sum < n + m - 1; sum++) {
            // UPRIGHT
            int col = min(m - 1, sum), row = sum - col; row++; col--;
            
            for (; row < n && col >= 0; row++, col--) {
                const int &prevval = grid[row - 1][col + 1];
                const int &gridval = grid[row][col];
                
                if (gridval == 1 || gridval != 2 - prevval) {
                    dp[row][col].two_turn[UPRIGHT] = dp[row][col].one_turn[UPRIGHT];
                } else {
                    dp[row][col].two_turn[UPRIGHT] = max({
                        dp[row][col].one_turn[UPRIGHT],
                        dp[row - 1][col + 1].two_turn[UPRIGHT] + 1,
                        dp[row - 1][col + 1].one_turn[DOWNRIGHT] + 1,
                    });
                }
            }

            // DOWNLEFT
            row = min(n - 1, sum), col = sum - row; row--; col++;
            for (; row >= 0 && col < m; row--, col++) {
                const int &prevval = grid[row + 1][col - 1];
                const int &gridval = grid[row][col];

                if (gridval == 1 || gridval != 2 - prevval) {
                    dp[row][col].two_turn[DOWNLEFT] = dp[row][col].one_turn[DOWNLEFT];
                } else {
                    dp[row][col].two_turn[DOWNLEFT] = max({
                        dp[row][col].one_turn[DOWNLEFT],
                        dp[row + 1][col - 1].two_turn[DOWNLEFT] + 1,
                        dp[row + 1][col - 1].one_turn[UPLEFT] + 1,
                    });
                }
            }
        }

        for (int diff = 0; diff < n + m - 1; diff++) {
            // UPLEFT
            int col = max(diff - n + 1, 0), row = n - 1 - diff + col; row++; col++;

            for (; row < n && col < m; row++, col++) {
                const int &prevval = grid[row - 1][col - 1];
                const int &gridval = grid[row][col];

                if (gridval == 1 || gridval != 2 - prevval) {
                    dp[row][col].two_turn[UPLEFT] = dp[row][col].one_turn[UPLEFT];             
                } else {
                    dp[row][col].two_turn[UPLEFT] = max({
                        dp[row][col].one_turn[UPLEFT],
                        dp[row - 1][col - 1].two_turn[UPLEFT] + 1,
                        dp[row - 1][col - 1].one_turn[UPRIGHT] + 1,
                    });
                }
            }

            // DOWNRIGHT
            col = min(diff, m - 1), row = n - 1 - (diff - col); col--; row--;
            for (; row >= 0 && col >= 0; row--, col--) {
                const int &prevval = grid[row + 1][col + 1];
                const int &gridval = grid[row][col];

                if (gridval == 1 || gridval != 2 - prevval) {
                    dp[row][col].two_turn[DOWNRIGHT] = dp[row][col].one_turn[DOWNRIGHT];
                } else {
                    dp[row][col].two_turn[DOWNRIGHT] = max({
                        dp[row][col].one_turn[DOWNRIGHT],
                        dp[row + 1][col + 1].two_turn[DOWNRIGHT] + 1,
                        dp[row + 1][col + 1].one_turn[DOWNLEFT] + 1,
                    });
                }
            }
        }
    }

    int get_max_clock_diag(int turn[], int dir) {
        switch (dir) {
            case UPRIGHT:
                return turn[DOWNRIGHT];
            case DOWNLEFT:
                return turn[UPLEFT];
            case UPLEFT:
                return turn[UPRIGHT];
            case DOWNRIGHT:
                return turn[DOWNLEFT];
            default:
                return -1;
        }
    }
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        const int n = grid.size(), m = grid[0].size();

        vve dp(n, ve(m));
        init_dp(dp, grid);
        process_one_turn(dp, grid);
        process_two_turn(dp, grid);

        const int drow[] = {-1, -1, 1, 1};
        const int dcol[] = {1, -1, 1, -1};
        int ans = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                if (grid[row][col] != 1) continue;
                ans = max(ans, 1);

                for (int dir = 0; dir < 4; dir++) {
                    int nrow = row + drow[dir], ncol = col + dcol[dir];
                    if (nrow < 0 || nrow >= n || ncol < 0 || ncol >= m) continue;
                    if (grid[nrow][ncol] != 2) continue;
                    ans = max(ans, max({
                        dp[nrow][ncol].two_turn[dir],
                        get_max_clock_diag(dp[nrow][ncol].one_turn, dir)
                    }) + 1);
                }
            }
        }

        return ans;
    }
};
