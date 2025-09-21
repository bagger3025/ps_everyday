#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

#define forn(i, x) for(int i = 0; i < int(x); i++)

void solve() {
	ll l, r; cin >> l >> r;

	ll ans = r - l + 1;

	ans -= r / 2 - (l - 1) / 2;
	ans -= r / 3 - (l - 1) / 3;
	ans -= r / 5 - (l - 1) / 5;
	ans -= r / 7 - (l - 1) / 7;

	ans += r / 6 - (l - 1) / 6;
	ans += r / 10 - (l - 1) / 10;
	ans += r / 14 - (l - 1) / 14;
	ans += r / 15 - (l - 1) / 15;
	ans += r / 21 - (l - 1) / 21;
	ans += r / 35 - (l - 1) / 35;

	ans -= r / 30 - (l - 1) / 30;
	ans -= r / 42 - (l - 1) / 42;
	ans -= r / 70 - (l - 1) / 70;
	ans -= r / 105 - (l - 1) / 105;

	ans += r / 210 - (l - 1) / 210;

	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(i, t) {
		solve();
	}
	return 0;
}
