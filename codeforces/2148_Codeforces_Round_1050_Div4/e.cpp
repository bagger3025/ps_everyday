#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void solve() {
	int n, k; cin >> n >> k;
	vector<int> a(n), cnts(n, 0);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--; cnts[a[i]]++;
	}

	for (int i = 0; i < n; i++) {
		if (cnts[i] % k != 0) {
			cout << 0 << endl; return;
		}
		cnts[i] /= k;
	}

	long long ret = 0;
	for (int lp = 0, rp = 0; lp < n; lp++) {
		while (rp < n && cnts[a[rp]] > 0) {
			cnts[a[rp]]--; rp++;
		}
		ret += rp - lp;
		cnts[a[lp]]++;
	}
	cout << ret << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	for (int tc = 0; tc < t; tc++) {
		solve();
	}
}
