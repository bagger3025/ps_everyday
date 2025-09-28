#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll; typedef vector<long long> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

const int MOD = 998'244'353;

bool is_valid(cvi &as, cvi &bs, int lidx, int ridx) {
	if (lidx < 0 || ridx >= as.size()) return true;

	return as[lidx] <= as[ridx] && bs[lidx] <= bs[ridx];
}

// from: incl, to: excl
ll rec(vi &as, vi &bs, int from, int to) {
	if (0 == to - from) {
		// cout << "as: "; for (auto &a: as) cout << a << " "; cout << "; bs: "; for (auto &a: bs) cout << a << " "; cout << endl;
	// cout << "rec(" << from << ", " << to << ") = " << 1 << endl;
		return 1;
	} else if (1 == to - from) {
		int ret = 0;
		if (is_valid(as, bs, from - 1, from) && is_valid(as, bs, from, from + 1)) ret++;
		swap(as[from], bs[from]);
		if (is_valid(as, bs, from - 1, from) && is_valid(as, bs, from, from + 1)) ret++;
		swap(as[from], bs[from]);
		// cout << "as: "; for (auto &a: as) cout << a << " "; cout << "; bs: "; for (auto &a: bs) cout << a << " "; cout << endl;
	// cout << "rec(" << from << ", " << to << ") = " << ret % MOD << endl;
		return ret;
	}
	int mid = (to + from) / 2;
	ll ret = 0;
	if (is_valid(as, bs, from - 1, mid) && is_valid(as, bs, mid, to)) {
		ll temp = rec(as, bs, from, mid);
		if (temp != 0) {
			temp = temp * rec(as, bs, mid + 1, to);
			temp %= MOD;
		}
		ret += temp;
	}
	swap(as[mid], bs[mid]);
	if (is_valid(as, bs, from - 1, mid) && is_valid(as, bs, mid, to)) {
		ll temp = rec(as, bs, from, mid);
		if (temp != 0) {
			temp = temp * rec(as, bs, mid + 1, to);
			temp %= MOD;
		}
		ret += temp;
	}
	swap(as[mid], bs[mid]);
		// cout << "as: "; for (auto &a: as) cout << a << " "; cout << "; bs: "; for (auto &a: bs) cout << a << " "; cout << endl;
	// cout << "rec(" << from << ", " << to << ") = " << ret % MOD << endl;
	return ret % MOD;
}

void solve() {
	int n; cin >> n;
	vi as(n), bs(n);

	for (int i = 0; i < n; i++) {
		cin >> as[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> bs[i];
	}

	cout << rec(as, bs, 0, n) << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase; cin >> testcase;

	for (int tc = 1; tc <= testcase; tc++) {
		solve();
	}
	return 0;
}
