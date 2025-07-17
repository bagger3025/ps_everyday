class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int allevens = 0;
        for (auto &n: nums) {
            allevens += (n & 1) ^ 1;
        }
        int all_same = max(allevens, (int)nums.size() - allevens);
 
        bool is_odd = nums[0] % 2;
        int odd_and_even = 1;
        for (int i = 1; i < nums.size(); i++) {
            int &n = nums[i];
            if (is_odd && (n % 2 == 0)) {
                odd_and_even++;
                is_odd = !is_odd;
            } else if (!is_odd && (n % 2 == 1)) {
                odd_and_even++;
                is_odd = !is_odd;
            }
        }
        return max(all_same, odd_and_even);
    }
};
