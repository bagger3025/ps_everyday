class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        sort(nums.begin(), nums.end());
        vector<pair<long long, int>> v;
        for (int i = 0, j = 0; i < nums.size();) {
            int val = nums[i];
            while (j < nums.size() && nums[j] == nums[i]) j++;
            v.push_back({val, j - i});
            i = j;
        }
        int s = 0, ans = 0;
        for (int i = 0, lp = 0, rp = 0; i < v.size(); i++) {
            while (lp < v.size() && v[lp].first < v[i].first - k) {
                s -= v[lp].second; lp++;
            }

            while (rp < v.size() && v[rp].first <= v[i].first + k) {
                s += v[rp].second; rp++;
            }

            // cout << "i = " << i << ", s = " << s << endl;
            ans = max(ans, v[i].second + min(numOperations, s - v[i].second));
        }
        
        s = 0;
        for (int lp = 0, rp = 0; rp < v.size(); lp++) {
            while (rp < v.size() && v[rp].first <= v[lp].first + k * 2) {
                s += v[rp].second; rp++;
            }
            ans = max(ans, min(numOperations, s));
            s -= v[lp].second;
        }

        return ans;
    }
};
