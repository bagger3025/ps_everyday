class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        const int row = mat.size(), col = mat[0].size();
        vector<int> ret; ret.reserve(row * col);

        for (int i = 0; i < row + col - 1; i++) {
            if (i % 2 == 0) {
                int r = min(i, row - 1);
                int c = i - r;
                while (r >= 0 && c < col) {
                    ret.push_back(mat[r][c]);
                    r--; c++;
                }
            } else {
                int c = min(i, col - 1);
                int r = i - c;
                while (r < row && c >= 0) {
                    ret.push_back(mat[r][c]);
                    r++; c--;
                }
            }
        }

        return ret;
    }
};
