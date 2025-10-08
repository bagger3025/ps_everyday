class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        const int n = rains.size();

        vector<int> ret(n, -1);
        set<int> frees;
        map<int, int> fulls;
        for (int i = 0; i < n; i++) {
            int r = rains[i];

            if (r == 0) {
                frees.insert(i);
                continue;
            }

            auto it = fulls.find(r);
            if (it == fulls.end()) {
                fulls[r] = i; continue;
            }

            int prev_full = it->second;
            auto frees_it = frees.lower_bound(prev_full);
            if (frees_it == frees.end()) return {};
            ret[*frees_it] = r;
            frees.erase(frees_it);
            it->second = i;
        }

        for (auto f: frees) {
            ret[f] = 1;
        }

        return ret;
    }
};
