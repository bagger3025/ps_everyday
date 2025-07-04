class Solution {
public:
    char kthCharacter(int k) {
        if (k == 1) return 'a';
        k--;
        int sum = 0;
        while (k > 0) {
            sum += k % 2;
            k /= 2;
        }
        return sum + 'a';
    }
};
