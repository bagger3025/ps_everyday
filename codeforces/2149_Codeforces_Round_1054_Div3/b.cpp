#include <iostream>
#include <algorithm>
#include <vector>

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

void solve(int n, vi &v) {
	sort(v.begin(), v.end());
	int maxval = v[1] - v[0];
	for (int i = 2; i < n; i += 2) {
		maxval = max(maxval, v[i + 1] - v[i]);
	}
	cout << maxval << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(i, t) {
		int n; cin >> n;
		vi v(n);
		forn(j, n) {
			cin >> v[j];
		}
		solve(n, v);
	}

	return 0;
}

