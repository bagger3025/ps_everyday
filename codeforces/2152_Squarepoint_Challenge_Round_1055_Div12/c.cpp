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

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

void solve(cvi &v, cvpii &query) {
	const int n = v.size();

	vi onecnt(n), conseq(n);
	onecnt[0] = v[0] == 1; conseq[0] = 0;
	for (int i = 1; i < n; i++) {
		onecnt[i] = onecnt[i - 1] + (v[i] == 1);
		conseq[i] = conseq[i - 1] + (v[i] == v[i - 1]);
	}

	for (auto &q: query) {
		int len = q.second - q.first + 1;
		if (len % 3 != 0) {
			cout << "-1\n"; continue;
		}
		int ones = onecnt[q.second] - (q.first == 0 ? 0 : onecnt[q.first - 1]);
		if (ones % 3 != 0) {
			cout << "-1\n"; continue;
		}

		int ans = len / 3;
		if (conseq[q.second] - conseq[q.first] == 0) {
			ans++;
		}

		cout << ans << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(tc, t) {
		int n, q; cin >> n >> q;
		vector<int> v(n); for (auto &e: v) cin >> e;
		vector<pii> query(q); for (auto &qele: query) {
			cin >> qele.first >> qele.second;
			qele.first--; qele.second--;
		}
		solve(v, query);
	}
}
