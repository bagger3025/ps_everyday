#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll; typedef vector<long long> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

void solve() {
	int n; cin >> n;
	vi v(n);
	int zerocnt = 0;
	ll total = (ll)n * (n + 1) / 2;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		if (v[i] == 0) zerocnt++;
		total -= v[i];
	}
	int lp = 0, rp = n - 1;
	while (lp < n) {
		if (v[lp] == 0) {
			if (zerocnt > 1) break;
			v[lp] = total;
		}
		if (v[lp] != lp + 1) break;

		lp++;
	}
	while (lp < rp) {
		if (v[rp] == 0) {
			if (zerocnt > 1) break;
			v[rp] = total;
		}
		if (v[rp] != rp + 1) break;
		rp--;
	}
	cout << rp - lp + 1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase; cin >> testcase;

	for (int tc = 1; tc <= testcase; tc++) {
		solve();
	}
	return 0;
}
