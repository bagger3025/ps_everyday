class Solution {
    typedef long long ll;
    ll getSum(ll l, ll r) {
        ll s = 0;
        for (ll from = 1, to = 4, i = 1; from <= r; from = to, to *= 4, i++) {
            if (to <= l) continue;
            ll cur_from = max(l, from);
            ll cur_to = min(r + 1, to);

            s += (cur_to - cur_from) * i;
        }

        return s;
    }
public:
    ll minOperations(vector<vector<int>>& queries) {
        ll ans = 0;
        for (auto q: queries) {
            int l = q[0], r = q[1];

            ll s = getSum(l, r);
            ans += s / 2 + s % 2;
        }
        return ans;
    }
};
