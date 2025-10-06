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
#define all(x) x.begin(), x.end()

typedef const int cint;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;
void solve(int z, cvi &v, cvpii &qry) {
	int maxval[2];
	for (auto [l, r]: qry) {
		if (r - l + 1 <= 2) {
			cout << r - l + 1 << endl; continue;
		}
		l--;
		maxval[0] = v[l++];
		maxval[1] = v[l++];
		int ret = 2;
		for (; l < r; l++) {
			if (maxval[0] + z < v[l]) {
				maxval[0] = v[l];
				ret++;
			} else if (maxval[1] + z < v[l]) {
				maxval[1] = v[l];
				ret++;
			}
		}
		
		cout << ret << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n, z; cin >> n >> z;
		vi v(n); for (int &e: v) cin >> e;
		int qn; cin >> qn;
		vpii qry(qn); for (auto &q: qry) cin >> q.first >> q.second;
		solve(z, v, qry);
	}
}
