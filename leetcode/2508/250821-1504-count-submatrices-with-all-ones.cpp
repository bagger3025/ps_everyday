class Solution {
    vector<vector<int>> getSquares(const vector<vector<int>> &mat) {
        const int row = mat.size(), col = mat[0].size();
        vector<vector<int>> ret(row, vector<int>(col));
        for (int i = 0; i < row; i++) {
            ret[i][0] = mat[i][0];
        }
        for (int i = 0; i < col; i++) {
            ret[0][i] = mat[0][i];
        }

        for (int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                if (mat[i][j] == 0) {
                    ret[i][j] = 0;
                    continue;
                }

                ret[i][j] = min({ret[i - 1][j], ret[i][j - 1], ret[i - 1][j - 1]}) + 1;
            }
        }
        return ret;
    }
public:
    int numSubmat(vector<vector<int>>& mat) {
        const int row = mat.size(), col = mat[0].size();

        vector<vector<int>> squares = getSquares(mat);

        int ans = 0;
        for (int i = 0; i < row; i++) {
            vector<int> cnt(col + 1, -1);
            cnt[0] = 0;
            for (int j = 0; j < col; j++) {
                const int &sq = squares[i][j];
                if (cnt[sq] == -1) {
                    cnt[sq] = j;
                } else {
                    for (int k = sq + 1; k < col && cnt[k] != -1; k++) {
                        ans += (j - cnt[k]) * (j - cnt[k] + 1) / 2;
                        cnt[k] = -1;
                    }
                }
            }
            for (int k = 1; k < col + 1 && cnt[k] != -1; k++) {
                ans += (col - cnt[k]) * (col - cnt[k] + 1) / 2;
            }
        }

        for (int i = 0; i < col; i++) {
            vector<int> cnt(row + 1, -1);
            cnt[0] = 0;
            for (int j = 0; j < row; j++) {
                const int &sq = squares[j][i];
                if (cnt[sq] == -1) {
                    cnt[sq] = j;
                } else {
                    for (int k = sq + 1; k < row && cnt[k] != -1; k++) {
                        ans += (j - cnt[k]) * (j - cnt[k] - 1) / 2;
                        cnt[k] = -1;
                    }
                }
            }
            for (int k = 1; k < row + 1 && cnt[k] != -1; k++) {
                ans += (row - cnt[k]) * (row - cnt[k] - 1) / 2;
            }
        }

        return ans;
    }
};
