class Solution {
    bool isBeautiful(int n) {
        int cnt[10] = { 0 };
        while (n > 0) {
            cnt[n % 10]++; n /= 10;
        }
        for (int i = 0; i < 10; i++) {
            if (cnt[i] != 0 && cnt[i] != i) return false;
        }
        return true;
    }
public:
    int nextBeautifulNumber(int n) {
        for (n++; true; n++) {
            if (isBeautiful(n)) return n;
        }
        return -1;
    }
};
