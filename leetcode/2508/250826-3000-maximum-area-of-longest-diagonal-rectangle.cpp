class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        const int n = dimensions.size();
        int w = dimensions[0][0], h = dimensions[0][1];
        int max_diag = w * w + h * h;
        int max_area = w * h;

        for (int i = 1; i < n; i++) {
            const int &w = dimensions[i][0];
            const int &h = dimensions[i][1];

            int diag = w * w + h * h;
            if (diag > max_diag) {
                max_diag = diag;
                max_area = w * h;
            } else if (diag == max_diag) {
                max_area = max(max_area, w * h);
            }
        }
        return max_area;
    }
};
