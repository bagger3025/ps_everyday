class Solution {
    void adjust_start(long long &start, const string &s) {
        int is_bigger = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            const int d = start % 10;
            if (d > s[i] - '0') {
                is_bigger = 1;
            } else if (d < s[i] - '0') {
                is_bigger = -1;
            }
            start /= 10;
        }
        if (is_bigger == 1) {
            start++;
        }
    }

    void adjust_finish(long long &finish, const string &s) {
        int is_bigger = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            const int d = finish % 10;
            if (d > s[i] - '0') {
                is_bigger = 1;
            } else if (d < s[i] - '0') {
                is_bigger = -1;
            }
            finish /= 10;
        }
        if (is_bigger == -1) {
            finish--;
        }
    }

    long long count_with_limit(long long start, long long finish, int limit) {
        if (start < 0 || finish < 0 || start > finish) return 0;

        int from = start % 10;
        int to = finish % 10;

        if (start < 10 && finish < 10) {
            return min(to, limit) - min(from, limit + 1) + 1;
        }

        if (start / 10 == finish / 10) {
            int cnt = min(to, limit) - min(from, limit + 1) + 1;
            if (cnt == 0) return 0;
            return count_with_limit(start / 10, start / 10, limit) * cnt;
        }

        long long ret = count_with_limit(start, start / 10 * 10 + 9, limit)
            + count_with_limit(start / 10 + 1, finish / 10 - 1, limit) * (limit + 1)
            + count_with_limit(finish / 10 * 10, finish, limit);

        return ret;
    }

public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        adjust_start(start, s);
        adjust_finish(finish, s);
        return count_with_limit(start, finish, limit);
    }
};
