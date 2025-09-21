#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef const vvl cvvl;

typedef pair<ll, ll> pll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef const vi cvi;
typedef const int ci;

typedef vector<bool> vb;

ll get_cnt(cvi &v, int from, int to) {
	unordered_set<int> s;

	for (int i = from; i <= to; i++) {
		s.insert(v[i]);
	}

	return s.size();
}

vl set_dp_zero(cvi &v, int n) {
	vb isexist(n, false);

	vl ret(n, 0);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (!isexist[v[i] - 1]) {
			isexist[v[i] - 1] = true;
			cnt++;
		}

		ret[i] = cnt;
	}
	return ret;
}

void naive(int n, int k, cvi &v) {
	vvl dp(k, vl(n, -1));

	dp[0] = set_dp_zero(v, n);

	for (int i = 1; i < k; i++)  {
		// There are total `i` numbers, which divide 0..(i-1) array into `i` arr
		//   ays
		dp[i][i] = i + 1;

		for (int j = i + 1; j < n; j++) {
			dp[i][j] = dp[i - 1][j - 1] + 1;

			for (int k = i - 1; k < j - 1; k++) {
				dp[i][j] = max(dp[i][j], dp[i - 1][k] + get_cnt(v, k + 1, j));
			}
		}
	}

	// for (auto &row: dp) {
	// 	for (auto &cell: row) {
	// 		cout << cell << " ";
	// 	} cout << endl;
	// } cout << endl;

	cout << dp[k - 1][n - 1] << endl;
}

void prefix_sum(int n, int k, cvi &v) {
	vvl dp(k, vl(n, -1));

	dp[0] = set_dp_zero(v, n);

	for (int i = 1; i < k; i++)  {
		// There are total `i` numbers, which divide 0..(i-1) array into `i` arr
		//   ays
		dp[i][i] = i;

		for (int j = i + 1; j < n; j++) {
			dp[i][j] = dp[i - 1][j - 1] + 1;
			vector<bool> exist(n, false);
			exist[v[j - 1] - 1] = true;
			int cnt = 1;

			for (int k = j - 2; k >= i - 1; k--) {
				if (!exist[v[k] - 1]) {
					exist[v[k] - 1] = true;
					cnt++;
				}
				dp[i][j] = max(dp[i][j], dp[i - 1][k] + cnt);
			}
		}
	}

	// for (auto &row: dp) {
	// 	for (auto &cell: row) {
	// 		cout << cell << " ";
	// 	} cout << endl;
	// } cout << endl;

	cout << dp[k - 1][n - 1] << endl;
}

pll simulate_twice(ci n, cvi &v, int mid) {
	cout << "mid = " << mid << endl;
	vl dp(n + 1);

	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		vector<bool> exists(n, false); exists[v[i - 1] - 1] = true;
		int cnt = 1;

		dp[i] = dp[i - 1] + 2 * cnt;

		for (int j = i - 2; j >= 0; j--) {
			if (!exists[v[j] - 1]) {
				exists[v[j] - 1] = true; cnt++;
			}

			dp[i] = max(dp[i], dp[j] + 2 * cnt);
		}
		dp[i] = dp[i] - mid;
	}
	cout << "dp: ";
	for (auto &d: dp) {
		cout << d << " ";
	}
	cout << endl;
	int k = 1;

	vi exists(n, false); exists[v[n - 1] - 1] = true;
	for (int i = n - 1, p = n, cnt = 1; i >= 1; i--) {
		if (dp[p] == dp[i] + 2 * cnt - mid) {
			exists = vi(n, false);
			cnt = 0;
			k++;
			p = i;
		}
		if (!exists[v[i - 1] - 1]) {
			exists[v[i - 1] - 1] = true;
			cnt++;
		}
	}
	cout << "k = " << k << endl;

	return {k, dp[n]};
}

class SegTree {
private:
	struct se {
		int l;
		int r;
		ll val;
		ll lazy;
	};

	typedef vector<se> vse;
	vse arr;

	void init_rec(int idx, int l, int r) {
		if (l + 1 == r) {
			arr[idx] = {l, r, 0, 0};
			return;
		}

		int mid = (l + r) / 2;
		init_rec(2 * idx + 1, l, mid);
		init_rec(2 * idx + 2, mid, r);

		arr[idx] = {l, r, 0, 0};
	}

	inline int get_lidx(int idx) {
		return 2 * idx + 1;
	}

	inline int get_ridx(int idx) {
		return 2 * idx + 2;
	}

	void resolve(int idx) {
		if (arr[idx].lazy == 0) return;

		if (arr[idx].l + 1 != arr[idx].r) {
			int lidx = get_lidx(idx);
			int ridx = get_ridx(idx);

			arr[lidx].lazy += arr[idx].lazy;
			arr[ridx].lazy += arr[idx].lazy;
		}

		arr[idx].val += arr[idx].lazy;
		arr[idx].lazy = 0;
	}

	pair<bool, ll> get_max_rec(int idx, int l, int r) {
		if (r <= arr[idx].l || arr[idx].r <= l) return {false, 0};

		resolve(idx);
		if (l <= arr[idx].l && arr[idx].r <= r) return {true, arr[idx].val}; 

		pair<bool, ll> lmax = get_max_rec(get_lidx(idx), l, r);
		pair<bool, ll> rmax = get_max_rec(get_ridx(idx), l, r);

		if (!lmax.first) {
			return rmax;
		} else if (!rmax.first) {
			return lmax;
		} else {
			return {true, max(lmax.second, rmax.second)};
		}
	}

	void add_lazy_rec(int idx, int l, int r, ll val) {
		if (r <= arr[idx].l || arr[idx].r <= l) return;

		if (l <= arr[idx].l && arr[idx].r <= r) {
			arr[idx].lazy += val;
			return;
		}

		resolve(idx);
		int lidx = get_lidx(idx), ridx = get_ridx(idx);
		add_lazy_rec(lidx, l, r, val);
		add_lazy_rec(ridx, l, r, val);
		resolve(lidx);
		resolve(ridx);

		arr[idx].val = max(arr[lidx].val, arr[ridx].val);
	}

	void set_val_rec(int idx, int x, ll val) {
		if (x < arr[idx].l || arr[idx].r <= x) return;

		if (arr[idx].l == x && x + 1 == arr[idx].r) {
			arr[idx].val = val; return;
		}

		int lidx = get_lidx(idx), ridx = get_ridx(idx);

		set_val_rec(lidx, x, val); set_val_rec(ridx, x, val);
		resolve(lidx); resolve(ridx);
		arr[idx].val = max(arr[lidx].val, arr[ridx].val);
	}
public:
	SegTree(int n): arr(4 * n) {
		init_rec(0, 0, n);
	}

	// exclusive r
	ll get_max(int r) {
		ll ret = get_max_rec(0, 0, r).second;
		return ret;
	}

	void add_lazy(int l, int r, ll val) {
		if (l >= r) return;
		add_lazy_rec(0, l, r, val);
	}

	void set_val(int x, ll val) {
		set_val_rec(0, x, val);
	}
};

pll simulate_twice_segtree(ci n, cvi &v, int mid) {
	// cout << "mid = " << mid << endl;
	vl dp(n + 1); dp[0] = 0;
	SegTree st(n + 1);
	vi lastidx(n, 0);

	for (int i = 1; i <= n; i++) {
		int start_idx = lastidx[v[i - 1] - 1];
		st.add_lazy(start_idx, i, 2);
		lastidx[v[i - 1] - 1] = i;

		dp[i] = st.get_max(i) - mid;

		st.set_val(i, dp[i]);
	}

	// cout << "dp: ";
	// for (auto &d: dp) {
	// 	cout << d << " ";
	// }
	// cout << endl;

	int k = 1, timestamp = 1;
	vi exists(n, 0); exists[v[n - 1] - 1] = timestamp;
	for (int i = n - 1, p = n, cnt = 1; i >= 1; i--) {
		if (dp[p] == dp[i] + 2 * cnt - mid) {
			timestamp++;
			cnt = 0;
			k++;
			p = i;
		}
		if (exists[v[i - 1] - 1] != timestamp) {
			exists[v[i - 1] - 1] = timestamp;
			cnt++;
		}
	}
	// cout << "k = " << k << endl;

	return {k, dp[n]};
}

void aliens_trick(int n, int k, cvi &v) {
	ll lp = -1, rp = n + 1;

	while (lp < rp) {
		ll mid = lp + (rp - lp) / 2;

		ll mid_k = simulate_twice(n, v, 2 * mid + 1).first;
		if (mid_k <= k) {
			rp = mid;
		} else {
			lp = mid + 1;
		}
	}

	ll res = simulate_twice(n, v, lp * 2).second;

	cout << res / 2 + lp * k << endl;
}

void aliens_segtree(int n, int k, cvi &v) {
	ll lp = -1, rp = n + 1;

	while (lp < rp) {
		ll mid = lp + (rp - lp) / 2;

		ll mid_k = simulate_twice_segtree(n, v, 2 * mid + 1).first;
		if (mid_k <= k) {
			rp = mid;
		} else {
			lp = mid + 1;
		}
	}
	// cout << "lp = " << lp << endl;

	ll res = simulate_twice_segtree(n, v, lp * 2).second;

	cout << res / 2 + lp * k << endl;
}

pll simulate_notwice_segtree(ci n, cvi &v, int mid) {
	// cout << "mid = " << mid << endl;
	vl dp(n + 1); dp[0] = 0;
	SegTree st(n + 1);
	vi lastidx(n, 0);

	for (int i = 1; i <= n; i++) {
		int start_idx = lastidx[v[i - 1] - 1];
		st.add_lazy(start_idx, i, 1);
		lastidx[v[i - 1] - 1] = i;

		dp[i] = st.get_max(i) - mid;

		st.set_val(i, dp[i]);
	}

	// cout << "dp: ";
	// for (auto &d: dp) {
	// 	cout << d << " ";
	// }
	// cout << endl;

	int k = 1, timestamp = 1;
	vi exists(n, 0); exists[v[n - 1] - 1] = timestamp;
	for (int i = n - 1, p = n, cnt = 1; i >= 1; i--) {
		if (dp[p] == dp[i] + cnt - mid) {
			timestamp++;
			cnt = 0;
			k++;
			p = i;
		}
		if (exists[v[i - 1] - 1] != timestamp) {
			exists[v[i - 1] - 1] = timestamp;
			cnt++;
		}
	}
	// cout << "k = " << k << endl;

	return {k, dp[n]};
}

void aliens_nodouble(int n, int k, cvi &v) {
	ll lp = 0, rp = n;
	ll res = n;

	while (lp < rp) {
		ll mid = lp + (rp - lp) / 2;

		auto ret = simulate_notwice_segtree(n, v, mid);
		ll mid_k = ret.first;
		res = min(res, ret.second + mid * k);

		if (mid_k <= k) {
			rp = mid;
		} else {
			lp = mid + 1;
		}
	}
	// cout << "lp = " << lp << endl;

	// ll res = simulate_notwice_segtree(n, v, lp).second;

	cout << res << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, k; cin >> n >> k;
	vi v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	// naive(n, k, v);
	// prefix_sum(n, k, v);
	// aliens_trick(n, k, v);
	// aliens_segtree(n, k, v);
	aliens_nodouble(n, k, v);

	return 0;
}
