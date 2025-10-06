#include <iostream>
#include <vector>

using namespace std;

void solve() {
	int n, m, x, y; cin >> n >> m >> x >> y;
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
	}
	for (int i = 0; i < m; i++) {
		int t; cin >> t;
	}
	cout << n + m << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	for (int tc = 0; tc < t; tc++) {
		solve();
	}
}
