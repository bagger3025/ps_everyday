class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        long long minval = 0, maxval = 0, t = 0;
        for (int i = 0; i < differences.size(); i++) {
            t += differences[i];
            minval = min(minval, t);
            maxval = max(maxval, t);
        }
        long long diff = maxval - minval;
        long long real_diff = upper - lower;
        return max(0LL, real_diff - diff + 1);
    }
};
