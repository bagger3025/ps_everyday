#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 998244353;

// n = qa + p
// na^(-1) = q + pa^(-1)
// -q = pa^(-1)
// -qp^(-1) = a^(-1)
long long rev_mod(long long r) {
	if (r == 0) return 0;
	if (r == 1) return 1;
	long long q = MOD / r;
	long long p = MOD % r;
	return ((-q * rev_mod(p)) % MOD + MOD) % MOD;
}

void solve() {
	long long n, x; cin >> n >> x;

	if (x < n * (n + 1) / 2 - 1) {
		cout << 0 << endl; return;
	} else if (n == 1) {
		cout << x << endl; return;
	}

	vector<long long> dp(x, 0);
	long long st = (n + 1) * (n - 2) / 2;

	dp[n + st - 1] = 1;

	for (int i = 1; i <= n - 1; i++) {
		for (int j = 0; j + i < x; j++) {
			dp[j + i] = (dp[j + i] + dp[j]) % MOD;
		}
	}

	for (int i = 1; i < x; i++) {
		dp[i] = (dp[i] + dp[i - 1]) % MOD;
	}
	long long s = 0;
	for (int i = 0; i < x; i++) {
		s = (s + dp[i]) % MOD;
	}
	cout << s << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase = 0; cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		solve();
	}
	return 0;
}
