class Solution {
    struct pq_ele {
        int val;
        int row; int col;

        bool operator<(const pq_ele &other) const {
            return this->val > other.val;
        }
    };

    const int dx[4] = {0, 0, -1, 1};
    const int dy[4] = {1, -1, 0, 0};
public:
    int swimInWater(vector<vector<int>>& grid) {
        const int n = grid.size();
        priority_queue<pq_ele> pq;
        pq.push({grid[0][0], 0, 0});

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        visited[0][0] = true;
        
        int maxval = 0;

        while (!pq.empty()) {
            auto t = pq.top(); pq.pop();
            maxval = max(maxval, t.val);
            if (t.row == n - 1 && t.col == n - 1) return maxval;

            for (int i = 0; i < 4; i++) {
                int trow = t.row + dx[i], tcol = t.col + dy[i];
                if (trow < 0 || trow >= n || tcol < 0 || tcol >= n) {
                    continue;
                }
                if (visited[trow][tcol]) continue;
                visited[trow][tcol] = true;
                pq.push({grid[trow][tcol], trow, tcol});
            }
        }
        return -1;
    }
};
