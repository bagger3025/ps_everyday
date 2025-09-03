bool points_cmp(const vector<int> &a, const vector<int> &b) {
    // y: lowest to highest
    if (a[1] != b[1]) return a[1] < b[1];
    // x: highest to lowest
    return a[0] > b[0];
}

class Solution {

public:
    int numberOfPairs(vector<vector<int>>& points) {
        const int n = points.size();
        sort(points.begin(), points.end(), points_cmp);

        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            int x_max = 1e9 + 1;
            const int &i_x = points[i][0];
            for (int j = i - 1; j >= 0; j--) {
                const int &j_x = points[j][0];
                if (j_x < i_x || j_x >= x_max) continue;
                ans++; x_max = j_x;
                if (j_x == i_x) break;
            }
        }
        return ans;
    }
};
