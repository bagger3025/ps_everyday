#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, q; cin >> n >> q;
	string s; cin >> s;
	for (int _q = 0; _q < q; _q++) {
		int x; cin >> x;
		if (x == 1) {
			char c; int i; cin >> c >> i; i--;
			s.insert(s.begin() + i, c);
		} else {
			int l, r; cin >> l >> r; l--; r--;
			string res = s.substr(l, r - l + 1);
			cout << res << "\n";
			s = s.substr(0, l) + s.substr(r + 1);
		}
	}
}
