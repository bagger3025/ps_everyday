class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        vector<pair<int, int>> v;
        v.reserve(reservedSeats.size());

        for (int i = 0; i < reservedSeats.size(); i++) {
            int val = reservedSeats[i][1] - 1;
            if (val == 0 || val == 9) continue;
            val = (val - 1) / 2;
            v.push_back({reservedSeats[i][0] - 1, val});
        }

        sort(v.begin(), v.end());

        int ans = 0;
        for (int lp = 0, vp = 0; lp < n; lp++) {
            if (vp == v.size()) {
                ans += (n - lp) * 2;
                break;
            }

            if (lp != v[vp].first) {
                ans += (v[vp].first - lp) * 2;
                lp = v[vp].first - 1;
                continue;
            }

            int t = 0, vmask = 0;
            while (vp < v.size() && v[vp].first == lp) {
                vmask |= 1 << v[vp].second;
                vp++;
            }

            if (vmask & 0b0011) {
                if (!(vmask & 0b0110)) {
                    ans++; continue;
                }
            } else {
                ans++;
            }
            if (!(vmask & 0b1100)) {
                ans++;
            }
        }

        return ans;
    }
};
