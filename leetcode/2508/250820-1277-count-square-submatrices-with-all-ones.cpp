class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int matrix_row = matrix.size(), matrix_col = matrix[0].size();
        int matrix_size = min(matrix_row, matrix_col);

        for (int i = 1; i < matrix_row; i++) {
            for (int j = 1; j < matrix_col; j++) {
                if (matrix[i][j] == 0) continue;
                matrix[i][j] = min({matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]}) + 1;
            }
        }

        int ans = 0;
        for (int i = 0; i < matrix_row; i++) {
            for (int j = 0; j < matrix_col; j++) {
                ans += matrix[i][j];
            }
        }
        return ans;
    }
};
