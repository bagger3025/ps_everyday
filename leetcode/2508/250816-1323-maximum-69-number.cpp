class Solution {
public:
    int maximum69Number (int num) {
        int d = 1;
        while (d < num) {
            d *= 10;
        }
        d /= 10;
        while (d > 0) {
            int digit = (num / d) % 10;
            if (digit == 6) {
                num += d * 3; break;
            }
            d /= 10;
        }
        return num;
    }
};
