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

void solve(int n, string &s) {
	int a_cnt = 0;
	forn(i, n) {
		a_cnt += (s[i] == 'a');
	}
	int b_cnt = n - a_cnt;

	long long move_a = 0, move_b = 0;
	int cnt = 0;

	// calculate move_a
	for (int lp = 0; lp < n; lp++) {
		if (s[lp] == 'a') {
			move_a += min(cnt, b_cnt - cnt);
		} else {
			cnt++;
		}
	}

	cnt = 0;
	// calculate move_b
	for (int lp = 0; lp < n; lp++) {
		if (s[lp] == 'b') {
			move_b += min(cnt, a_cnt - cnt);
		} else {
			cnt++;
		}
	}
	cout << min(move_a, move_b) << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(i, t) {
		int n; cin >> n;
		string s; cin >> s;
		solve(n, s);
	}

	return 0;
}

