class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        int lp = 0, rp = 0;
        long long ans = 0, pairs = 0;
        unordered_map<int, int> cnts;

        while (rp < nums.size()) {
            int prev_rp = rp;
            while (rp < nums.size() && pairs < k) {
                int &cnt = cnts[nums[rp]];
                pairs += cnt;
                cnt++; rp++;
            }
            int mid = rp - prev_rp;
            if (pairs >= k) mid--;
            ans += lp * mid;
            if (pairs < k) break;            

            while (lp < rp && pairs >= k) {
                int &cnt = cnts[nums[lp]];
                pairs -= cnt - 1;
                cnt--; lp++;
            }
            ans += lp;
        }
        return ans;
    }
};
