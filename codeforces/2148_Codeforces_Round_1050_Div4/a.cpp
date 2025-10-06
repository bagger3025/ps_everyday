#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	for (int tc = 0; tc < t; tc++) {
		int x, n; cin >> x >> n;
		if (n % 2 == 0) {
			cout << "0\n";
		} else {
			cout << x << "\n";
		}
	}
}
