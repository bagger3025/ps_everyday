#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)

typedef vector<int> vi;
typedef const vi cvi;

void solve(cvi &v) {
	const int n = 0;
	vector<bool> cnt(100, false);
	int val = 0;

	for (auto &ele: v) {
		if (cnt[ele - 1] == false) {
			cnt[ele - 1] = true;
			val++;
		}
	}
	cout << (val * 2) - 1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(tc, t) {
		int n; cin >> n;
		vector<int> v(n);
		for (auto &e: v) cin >> e;
		solve(v);

	}
}
