class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        int pairs = 0, middle = 0;
        vector<int> visited(26 * 26, 0);
        for (const auto &w: words) {
            const int idx = (w[0] - 'a') * 26 + (w[1] - 'a');
            const int revidx = (w[1] - 'a') * 26 + (w[0] - 'a');
            if (visited[revidx]) {
                visited[revidx]--; pairs++;
                if (w[0] == w[1]) middle--;
            } else {
                visited[idx]++;
                if (w[0] == w[1]) middle++;
            }
        }
        return pairs * 4 + (middle ? 2 : 0);
    }
};
