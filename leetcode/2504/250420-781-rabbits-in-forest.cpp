class Solution {
public:
    int numRabbits(vector<int>& answers) {
        vector<int> anscnt(1000, 0);
        int ans = 0;
        for (auto &a: answers) {
            if (anscnt[a] % (a + 1) == 0) ans += a + 1;
            anscnt[a]++;
        }
        return ans;
    }
};
