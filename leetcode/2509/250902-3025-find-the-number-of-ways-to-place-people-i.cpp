class Solution {
    int isRightDown(const vector<int> &p1, const vector<int> &p2) {
        const int &p1x = p1[0], &p1y = p1[1], &p2x = p2[0], &p2y = p2[1];

        if (p1x > p2x && p1y < p2y) return 0;
        if (p1x < p2x && p1y > p2y) return 1;
        if (p1x == p2x) return p1y < p2y ? 0 : 1;
        if (p1y == p2y) return p1x < p2x ? 1 : 0;
        return -1;
    }

    int getCnt(const int &rightdown, const int &leftup, const vector<vector<int>> &points) {
        const int n = points.size();

        const int &xl = points[leftup][0], &xt = points[rightdown][0];
        const int &yl = points[rightdown][1], &yt = points[leftup][1];

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            const int &x = points[i][0], &y = points[i][1];

            if (xl <= x && x <= xt && yl <= y && y <= yt) cnt++;
        }

        return cnt;
    }
public:
    int numberOfPairs(vector<vector<int>>& points) {
        const int n = points.size();

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int rightdown = isRightDown(points[i], points[j]);
                if (rightdown == -1) continue;
                
                int rightidx = rightdown == 0 ? i : j;
                int leftidx = rightdown == 0 ? j : i;

                int cnt = getCnt(rightidx, leftidx, points);
                if (cnt == 2) ans++;
            }
        }

        return ans;
    }
};
