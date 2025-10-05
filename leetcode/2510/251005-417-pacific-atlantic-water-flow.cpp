class Solution {
    const int PACIFIC = 0b1;
    const int ATLANTIC = 0b10;

    const int dx[4] = {0, 0, 1, -1};
    const int dy[4] = {1, -1, 0, 0};

    void bfs(vector<vector<int>> &visited, int val, queue<pair<int, int>> &q, vector<vector<int>> &heights) {
        const int n = visited.size(), m = visited[0].size();
        while (!q.empty()) {
            auto [row, col] = q.front(); q.pop();

            for (int i = 0; i < 4; i++) {
                int trow = row + dx[i], tcol = col + dy[i];
                if (trow < 0 || trow >= n || tcol < 0 || tcol >= m) continue;
                if (visited[trow][tcol] & val) continue;
                if (heights[trow][tcol] < heights[row][col]) continue;
                visited[trow][tcol] |= val;
                q.push({trow, tcol});
            }
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const int n = heights.size(), m = heights[0].size();
        vector<vector<int>> mark(n, vector<int>(m, 0));

        queue<pair<int, int>> q;
        mark[0][0] |= PACIFIC;
        for (int i = 1; i < m; i++) {
            mark[0][i] |= PACIFIC;
            q.push({0, i});
        }
        for (int i = 1; i < n; i++) {
            mark[i][0] |= PACIFIC;
            q.push({i, 0});
        }
        bfs(mark, PACIFIC, q, heights);

        mark[n - 1][m - 1] |= ATLANTIC;
        for (int i = 0; i < m - 1; i++) {
            mark[n - 1][i] |= ATLANTIC;
            q.push({n - 1, i});
        }
        for (int i = 0; i < n - 1; i++) {
            mark[i][m - 1] |= ATLANTIC;
            q.push({i, m - 1});
        }
        bfs(mark, ATLANTIC, q, heights);

        vector<vector<int>> ans;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mark[i][j] == 0b11) {
                    ans.push_back({i, j});
                }
            }
        }
        return ans;
    }
};
