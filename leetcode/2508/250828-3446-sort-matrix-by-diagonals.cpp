class Solution {
    typedef vector<int> vi;
    typedef vector<vi> vvi;

    void _sortMatrix(vvi &grid, int diff) {
        #define GRID(row) (grid[row][row - diff])
        const int n = grid.size();

        int from_row = max(0, diff);
        int to_row = n - 1 + min(0, diff); // inclusive

        for (int r = from_row + 1; r <= to_row; r++) {
            int target = GRID(r);
            int j;
            for (j = r - 1; j >= from_row; j--) {
                if (diff < 0) {
                    if (GRID(j) > target) {
                        GRID(j + 1) = GRID(j);
                    } else break;
                } else {
                    if (GRID(j) < target) {
                        GRID(j + 1) = GRID(j);
                    } else break;
                }
            }
            GRID(j + 1) = target;
        }

        #undef GRID
    }

public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        const int n = grid.size();

        // row - col = diff
        for (int diff = n - 1 - 1; diff > -(n - 1); diff--) {
            _sortMatrix(grid, diff);
        }
        return grid;
    }
};
