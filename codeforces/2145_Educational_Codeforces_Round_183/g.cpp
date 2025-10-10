#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define all(x) x.begin(), x.end()

typedef const int cint;

typedef long long ll; typedef vector<ll> vll; typedef vector<vll> vvll;
typedef const ll cll; typedef const vll cvll; typedef const vvll cvvll;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

const int MOD = 998'244'353;

// MOD = q * a + p
// p * a^(-1) = -q
// a^(-1) = -q * p^(-1)
int rev_mod(int a) {
	return a == 1 ? 1 : MOD - ((ll)(MOD / a) * rev_mod(MOD % a)) % MOD;
}

vll get_comb(int n) {
	vll ret(n + 1);
	ret[0] = 1;
	for (int i = 1; i <= n / 2; i++) {
		ret[i] = ((ret[i - 1] * (n + 1 - i)) % MOD * rev_mod(i)) % MOD;
	}
	for (int i = n / 2 + 1; i <= n; i++) {
		ret[i] = ret[n - i];
	}
	return ret;
	
}

ll get_ans(cvll &cur_dp, cint &n, cint &m, int x, int y, cvll &xcomb, cvll &ycomb) {
	// cout << "x = " << x << ", y = " << y << endl;
	ll ret = ((cur_dp[n + m - x - y] * xcomb[x]) % MOD * ycomb[y]) % MOD;
	// cout << "ret = " << ret << endl;

	return ret;
}

void solve(int n, int m, int k) {
	vll dp[2] = { vll(n + m, 0), vll(n + m) };
	dp[0][0] = 1;

	for (int i = 1; i < k; i++) {
		vll &cur_dp = dp[i & 1], &prev_dp = dp[(i & 1) ^ 1];
		cur_dp[0] = 0;

		for (int j = 1; j < n + m; j++) {
			cur_dp[j] = ((cur_dp[j - 1] * i) % MOD + (prev_dp[j - 1] * (k - i)) % MOD) % MOD;
		}
	}

	vll &cur_dp = dp[(k - 1) & 1];

	// cout << "Result dp: ";
	// for (auto d: cur_dp) {
	// 	cout << d << " ";
	// } cout << endl;

	vll n_combs = get_comb(n), m_combs = get_comb(m);

	// cout << "n_combs: ";
	// for (auto &d: n_combs) {
	// 	cout << d << " ";
	// } cout << endl;

	for (int i = min(n, m); i <= n + m - 1; i++) {
		ll ans = 0;
		int maxval = n + m - i;
		// cout << endl << endl << "maxval = " << maxval << endl;
		if (maxval <= m) {
			for (int x = 1; x <= min(n, maxval - 1); x++) {
				ans = (ans + get_ans(cur_dp, n, m, x, maxval, n_combs, m_combs)) % MOD;
			}
		}
		if (maxval <= n) {
			for (int y = 1; y <= min(m, maxval - 1); y++) {
				ans = (ans + get_ans(cur_dp, n, m, maxval, y, n_combs, m_combs)) % MOD;
			}
		}
		if (maxval <= n && maxval <= m) {
			ans = (ans + get_ans(cur_dp, n, m, maxval, maxval, n_combs, m_combs)) % MOD;
		}

		cout << ans << " ";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m, k; cin >> n >> m >> k;

	solve(n, m, k);
}
