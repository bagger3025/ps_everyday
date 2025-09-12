#include <iostream>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
	if (a > b) swap(a, b);
	if (a == 0) return b;
	return gcd(b % a, a);
}

void solve() {
	long long a, b, k; cin >> a >> b >> k;

	long long g = gcd(a, b);
	a /= g; b /= g;

	if (a <= k && b <= k) cout << 1 << endl;
	else cout << 2 << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase; cin >> testcase;

	for (int tc = 1; tc <= testcase; tc++) {
		solve();
	}
	return 0;
}
