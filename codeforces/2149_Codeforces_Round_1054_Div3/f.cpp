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

void solve(ll h, cint &d) {
	if (h == 1) {
		cout << 2 * d << "\n";
		return;
	}
	if (d == 1) {
		cout << "1\n";
		return;
	}
	ll lp = 1, rp = d;
	while (lp < rp) {
		ll mid = (lp + rp) / 2;

		ll q = d / mid, r = d % mid;

		ll expected_h = (mid - r) * (q * (q + 1) / 2) + r * ((q + 1) * (q + 2) / 2);
		// cout << "mid = " << mid << ", expected_h = " << expected_h << endl;
		if (h + (mid - 1) > expected_h) {
			rp = mid;
		} else {
			lp = mid + 1;
		}
	}
	// cout << "rp = " << rp << endl;
	cout << rp - 1 + d << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(i, t) {
		int h, d; cin >> h >> d;
		solve(h, d);
	}

	return 0;
}

