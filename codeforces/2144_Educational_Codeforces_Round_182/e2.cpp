#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 998244353;

typedef long long ll; typedef vector<ll> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const int cint; typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

typedef pair<ll, ll> pll; typedef vector<pll> vpll;
typedef const pll cpll; typedef const vpll cvpll;

typedef const string cstr;

#define forn(i, n) for (int i = 0; i < int(n); i++)

// mod = q * a + p
// a^-1 * mod = q + p * a^-1
// a^-1 = -q * p^-1
int rev_mod(int r, cint &mod = MOD) {
	return r == 1 ? 1 : MOD - (mod / r) * rev_mod(mod % r);
}

ll pow_mod(int a, int p, cint &mod = MOD) {
	if (p == 0) return 1;
	if (p == 1) return a;
	ll ret = pow_mod(a, p / 2, mod);
	ret = (ret * ret) % mod;
	if (p % 2 == 1) {
		return (ret * a) % mod;
	} else {
		return ret;
	}
}

vi get_hset(cvi &v) {
	vi ret;
	ret.push_back(v[0]);
	for (int i = 1; i < v.size(); i++) {
		if (ret.back() < v[i]) ret.push_back(v[i]);
	}
	return ret;
}

int find_hset_idx(int val, cvi &v) {
	int lp = 0, rp = v.size();
	while (lp < rp) {
		int mid = (lp + rp) / 2;
		if (v[mid] > val) {
			rp = mid;
		} else {
			lp = mid + 1;
		}
	}
	return lp < v.size() && v[lp] == val ? lp : -1;
}

void naive_dp(vl &dp, cvi &v, cvi &hset, int idx = 0, int hset_idx = 0, ll val = 1, bool flag = false) {
	if (idx == v.size()) return;

	if (hset_idx < hset.size() && v[idx] == hset[hset_idx]) {
		dp[idx] = (dp[idx] + val) % MOD;

		if (hset_idx != hset.size() - 1) {
			// see next hset_idx, select this index
			naive_dp(dp, v, hset, idx + 1, hset_idx + 1, val, false);

			// selecting this index, not changing hset_idx
			naive_dp(dp, v, hset, idx + 1, hset_idx, val, true);
		}
		// not selecting this index
		naive_dp(dp, v, hset, idx + 1, hset_idx, val, flag);
	} else if (
		(!flag && hset_idx > 0 && v[idx] < hset[hset_idx - 1]) ||
		(flag && hset_idx < hset.size() && v[idx] < hset[hset_idx])
	) {
		// selecting this index & not selecting
		naive_dp(dp, v, hset, idx + 1, hset_idx, (val * 2) % MOD, flag);
	} else {
		// not selecting this index
		naive_dp(dp, v, hset, idx + 1, hset_idx, val, flag);
	}
}

void naive(cvi &v) {
	const int n = v.size();

	vi v_reverse(v.crbegin(), v.crend());
	vi lh = get_hset(v), rh = get_hset(v_reverse);

	vl forward_dp(n, 0), backward_dp(n, 0);

	naive_dp(forward_dp, v, lh);
	naive_dp(backward_dp, v_reverse, rh);

	std::reverse(backward_dp.begin(), backward_dp.end());

	// cout << "forward_dp: ";
	// for (auto &d: forward_dp) {
	// 	cout << d << " ";
	// } cout << endl;
	// cout << "backward_dp: ";
	// for (auto &d: backward_dp) {
	// 	cout << d << " ";
	// } cout << endl;

	int highest = lh.back();
	ll ans = 0;
	forn(i, n) {
		if (v[i] != highest) continue;
		for (int j = i; j < n; j++) {
			if (v[j] != highest) continue;
			ans = (ans + ((forward_dp[i] * backward_dp[j]) % MOD) * pow_mod(2, max(0, j - i - 1))) % MOD;
		}
	}
	cout << ans << "\n";
}

int find_ceil(int val, cvi &v) {
	int lp = 0, rp = v.size() - 1;
	while (lp < rp) {
		int mid = (lp + rp) / 2;
		if (val <= v[mid]) {
			rp = mid;
		} else {
			lp = mid + 1;
		}
	}
	return lp;
}

void fenwick_add(vi &v, int idx, int val) {
	while (idx < v.size()) {
		v[idx] += val;
		idx |= idx + 1;
	}
}

int fenwick_sum(vi &v, int til) {
	int ret = 0;
	while (til >= 0) {
		ret += v[til];
		til -= (~til) & (til + 1);
	}
	return ret;
}

void solve_dp(vl &dp, vl &par, cvi &v, cvi &hset) {
	const int n = v.size();

	vi hset_idx(n);
	forn(i, n) {
		hset_idx[i] = find_ceil(v[i], hset);
	}

	vi prefix_sums(hset.size(), 0);
	vi prev_sums(n);
	vi last_idx(hset.size(), -1);

	forn(i, n) {
		fenwick_add(prefix_sums, hset_idx[i], 1);
		if (hset[hset_idx[i]] != v[i]) continue;

		if (hset_idx[i] == 0) {
			dp[i] = 1;
			par[i] = 1;
		} else if (last_idx[hset_idx[i] - 1] != -1) {
			ll acc_sum = fenwick_sum(prefix_sums, hset_idx[i] - 1) - prev_sums[last_idx[hset_idx[i] - 1]];
			acc_sum = dp[last_idx[hset_idx[i] - 1]] * pow_mod(2, acc_sum);
			acc_sum %= MOD;

			dp[i] = acc_sum;
			par[i] = acc_sum;
		}

		const int &same_idx = last_idx[hset_idx[i]];
		prev_sums[i] = fenwick_sum(prefix_sums, hset_idx[i]);
		if (same_idx != -1) {
			ll acc_sum = prev_sums[i] - prev_sums[same_idx];
			dp[i] = (dp[i] + (dp[same_idx] * pow_mod(2, acc_sum) % MOD)) % MOD;
		}
		last_idx[hset_idx[i]] = i;
	}
}

void solve(cvi &v) {
	const int n = v.size();

	vi v_reverse(v.crbegin(), v.crend());
	vi lh = get_hset(v), rh = get_hset(v_reverse);

	vl forward_dp(n, 0), backward_dp(n, 0);
	vl forward_par(n, 0), backward_par(n, 0);
	solve_dp(forward_dp, forward_par, v, lh);
	solve_dp(backward_dp, backward_par, v_reverse, rh);

	// cout << "forward dp: ";
	// for (auto &dp: forward_dp) {
	// 	cout << dp << " ";
	// } cout << endl;
	// cout << "forward par: ";
	// for (auto &dp: forward_par) {
	// 	cout << "{"<< dp.first << ", " << dp.second << "} ";
	// } cout << endl;
	// cout << "backward dp: ";
	// for (auto &dp: backward_dp) {
	// 	cout << dp << " ";
	// } cout << endl;
	// cout << "backward par: ";
	// for (auto &dp: backward_par) {
	// 	cout << "{"<< dp.first << ", " << dp.second << "} ";
	// } cout << endl;
	// cout << endl;

	cint max_height = lh.back();
	ll ans = 0;
	forn(i, n) {
		if (v[i] != max_height) continue;
		ans += (forward_par[i] * (backward_dp[n - 1 - i] + MOD - ((backward_dp[n - 1 - i] - backward_par[n - 1 - i]) * rev_mod(2)) % MOD)) % MOD;
		ans %= MOD;
	}
	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase = 0; cin >> testcase;
	forn(i, testcase) {
		int n; cin >> n;
		vi v(n);
		forn(j, n) {
			cin >> v[j];
		}
		// naive(v);
		solve(v);
	}
	return 0;
}
