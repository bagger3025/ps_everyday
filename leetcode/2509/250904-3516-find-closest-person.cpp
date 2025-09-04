class Solution {
    int int_abs(int x) {
        return x > 0 ? x : -x;
    }
public:
    int findClosest(int x, int y, int z) {
        int dist1 = int_abs(x - z);
        int dist2 = int_abs(y - z);
        if (dist1 == dist2) return 0;
        if (dist1 > dist2) return 2;
        return 1;
    }
};
