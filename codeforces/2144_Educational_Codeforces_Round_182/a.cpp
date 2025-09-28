#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll; typedef vector<long long> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

void solve() {
	int n; cin >> n;
	vi v(n);
	int s = 0;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		s += v[i];
	}
	if (s % 3 != 0) {
		cout << "0 0\n";
	} else {
		cout << "1 2\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase; cin >> testcase;

	for (int tc = 1; tc <= testcase; tc++) {
		solve();
	}
	return 0;
}
