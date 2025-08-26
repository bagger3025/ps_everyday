class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int rowlp = grid.size(), rowrp = 0, collp = grid[0].size(), colrp = 0;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 0) continue;

                rowlp = min(rowlp, i);
                rowrp = max(rowrp, i);
                collp = min(collp, j);
                colrp = max(colrp, j);
            }
        }
        if (rowlp > rowrp || collp > colrp) return 0;
        return (rowrp - rowlp + 1) * (colrp - collp + 1);
    }
};
