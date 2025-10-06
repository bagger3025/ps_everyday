#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// const int MOD = 998244353;

typedef long long ll; typedef vector<ll> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi; typedef vector<vvi> vvvi;
typedef const int cint; typedef const vi cvi; typedef const vvi cvvi; typedef const vvvi cvvvi;

typedef vector<string> vs;
typedef const vs cvs;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

typedef pair<ll, ll> pll; typedef vector<pll> vpll;
typedef const pll cpll; typedef const vpll cvpll;

typedef const string cstr;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define all(x) (x).begin(), (x).end()

class SegTree {
	static const int MAXVAL_LEN = 2;
	struct ele {
		int l;
		int r;
		int maxval[MAXVAL_LEN] = {-1, -1};
		int cnt[MAXVAL_LEN] = { 0 };

		void _set_maxval(int val, int c) {
			forn(i, MAXVAL_LEN) {
				if (maxval[i] == val) {
					cnt[i] += c;
					if (cnt[0] < cnt[1]) {
						swap(cnt[0], cnt[1]);
						swap(maxval[0], maxval[1]);
					}
					return;
				}
				if (maxval[i] == -1) {
					maxval[i] = val; cnt[i] = c;
					if (cnt[0] < cnt[1]) {
						swap(cnt[0], cnt[1]);
						swap(maxval[0], maxval[1]);
					}
					return;
				}
			}

			int v = min(c, cnt[MAXVAL_LEN - 1]);
			forn(i, MAXVAL_LEN) {
				cnt[i] -= v;
			}
			c -= v;
			forn(i, MAXVAL_LEN) {
				if (cnt[i] != 0) continue;
				if (c != 0) {
					maxval[i] = val; cnt[i] = c;
					if (cnt[0] < cnt[1]) {
						swap(cnt[0], cnt[1]);
						swap(maxval[0], maxval[1]);
					}
					c = 0;
				} else {
					maxval[i] = -1;
				}
			}
		}

		void set_maxval(const ele &e1, const ele &e2) {
			for (int i = 0; i < MAXVAL_LEN; i++) {
				maxval[i] = e1.maxval[i];
				cnt[i] = e1.cnt[i];
			}

			for (int i = 0; i < MAXVAL_LEN; i++) {
				if (e2.maxval[i] == -1) continue;
				_set_maxval(e2.maxval[i], e2.cnt[i]);
			}
		}

		ele(int l, int r, const ele &e1, const ele &e2): l(l), r(r) {
			set_maxval(e1, e2);
		}

		ele(int l, int r, const int &val): l(l), r(r), maxval{val, -1}, cnt{1} {}
		ele(): l(0), r(0), maxval{-1, -1}, cnt{} {}
	};

	friend ostream &operator<<(ostream &os, const ele &e) {
		cout << "{l=" << e.l << ", r=" << e.r << ", maxval={"<< e.maxval[0] << ", " << e.maxval[1] << "}, cnt={" << e.cnt[0] << ", " << e.cnt[1] << "}}";
		return os;
	}

	vector<ele> arr;
	int n;

	inline int left(int idx) { return idx * 2 + 1; }
	inline int right(int idx) { return idx * 2 + 2; }

	

	void init(int idx, int l, int r, cvi &v) {
		if (l == r) {
			arr[idx] = ele(l, r, v[l]);
			return;
		}

		int mid = (l + r) / 2;
		init(left(idx), l, mid, v);
		init(right(idx), mid + 1, r, v);
		arr[idx] = ele(l, r, arr[left(idx)], arr[right(idx)]);
	}

	ele rec_dominates(int idx, int l, int r) {
		ele &e = arr[idx];
		if (e.r < l || r < e.l) return ele();
		if (l <= e.l && e.r <= r) return e;

		ele e1 = rec_dominates(left(idx), l, r);
		ele e2 = rec_dominates(right(idx), l, r);

		ele ret = ele(0, 0, e1, e2);
		// cout << "idx = " << idx << ", e1 = " << e1 << ", e2 = " << e2 << ", ret = " << ret << endl;
		return ret;
	}

public:
	SegTree(cvi &v): arr(4 * v.size()), n(v.size()) {
		init(0, 0, n - 1, v);
	}

	void print() const {
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i] << " ";
		} cout << endl;
	}

	pair<int, int> get_dominates(int l, int r) {
		r--;
		ele t = rec_dominates(0, l, r);
		return {t.maxval[0], t.maxval[1]};
	}
};

void solve(vi &v, cvpii &queries) {
	cint n = v.size();

	map<int, int> val_to_idx;
	vi idx_to_val;
	vvi idx_to_indices;
	forn(i, n) {
		auto it = val_to_idx.find(v[i]);
		int idx;
		if (it == val_to_idx.end()) {
			idx = idx_to_indices.size();
			val_to_idx[v[i]] = idx;
			idx_to_indices.push_back(vi());
			idx_to_val.push_back(v[i]);
		} else {
			idx = it->second;
		}

		v[i] = idx;
		idx_to_indices[idx].push_back(i);
	}

	SegTree st(v);
	// st.print();

	for (auto [l, r]: queries) {
		l--;
		int target_cnt = (r - l) / 3 + 1;
		pii cands = st.get_dominates(l, r);
		// cout << cands.first << ", " << cands.second << endl;
		vi ret;
		if (cands.first != -1) {
			// cout << "first = " << idx_to_val[cands.first] << endl;
			if (lower_bound(all(idx_to_indices[cands.first]), r) - lower_bound(all(idx_to_indices[cands.first]), l) >= target_cnt) {
				ret.push_back(idx_to_val[cands.first]);
			}
		}
		if (cands.second != -1) {
			// cout << "second = " << idx_to_val[cands.second] << endl;
			if (lower_bound(all(idx_to_indices[cands.second]), r) - lower_bound(all(idx_to_indices[cands.second]), l) >= target_cnt) {
				ret.push_back(idx_to_val[cands.second]);
			}
		}

		if (ret.size() == 2 && ret[0] > ret[1]) swap(ret[0], ret[1]);
		if (ret.size() == 0) {
			cout << "-1\n";
		} else if (ret.size() == 1) {
			cout << ret[0] << "\n";
		} else {
			cout << ret[0] << " " << ret[1] << "\n";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(i, t) {
		int n, q; cin >> n >> q;
		vi v(n); for (auto &ele: v) cin >> ele;
		vpii queries(q); for (auto &qele: queries) cin >> qele.first >> qele.second;
		solve(v, queries);
	}

	return 0;
}

