#include <iostream>
#include <vector>

using namespace std;

int run_until(int &t, const int &a, int &side, const int &b) {
	int ret = 0;
	int time_diff = (a - 1) - t;
	ret = time_diff;
	side = side ^ (time_diff % 2);
	if (b != -1) {
		ret += side != b;
		side = b;
	} else {
		ret += 1;
		side = side ^ 1;
	}
	t = a;
	return ret;
}

void solve() {
	int n, m; cin >> n >> m;
	int t = 0, side = 0;
	int score = 0;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		score += run_until(t, a, side, b);
	}
	score += run_until(t, m, side, -1);

	cout << score << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	for (int tc = 0; tc < t; tc++) {
		solve();
	}
}
