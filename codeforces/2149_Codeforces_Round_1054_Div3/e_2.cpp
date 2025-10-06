#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int MOD = 998244353;

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

void solve(int n, int k, int l, int r, cvi &v) {
	map<int, int> m;

	long long ans = 0;
	for (int lp = 0, rp = 0, rp2 = 0; lp + l <= n; lp++) {
		while (rp < n && rp < lp + r) {
			if (rp < lp + l || m.size() < k) {
				m[v[rp]]++;
				// print_m(m);
				rp++;
			} else {
				break;
			}
		}
		if (rp2 < rp) rp2 = rp;
		if (m.size() == k) {
			while (rp2 < n && rp2 < lp + r) {
				if (m.find(v[rp2]) == m.end()) break;
				// cout << "m found " << v[rp2] << endl;
				rp2++;
			}
			ans += rp2 - (rp - 1);
		}
		// cout << "lp = " << lp << ", rp = " << rp << ", rp2 = " << rp2 << endl;

		int lp_val = --m[v[lp]];
		if (lp_val == 0) {
			m.erase(m.find(v[lp]));
		}
	}
	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(i, t) {
		int n, k, l, r; cin >> n >> k >> l >> r;
		vi v(n);
		forn(j, n) {
			cin >> v[j];
		}
		solve(n, k, l, r, v);
	}

	return 0;
}


