#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define all(x) x.begin(), x.end()

int MOD = 676'767'677;

typedef const int cint;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

void solve(int n, cvi &v) {
	pii left = {1, 1}, right = {1, 1};
	for (int i = 1; i < n; i++) {
		if (v[i - 1] + 1 == v[i]) {
			left.first = 0;
		} else if (v[i - 1] == v[i]) {
			swap(left, right);
		} else if (v[i - 1] - 1 == v[i]) {
			right.first = 0;
		} else {
			left.first = 0, right.first = 0;
			break;
		}
		left.second += left.first;
	}
	if (left.second != v[0]) left.first = 0;
	if (right.second != v[0]) right.first = 0;

	cout << left.first + right.first << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n; cin >> n;
		vi v(n); for (auto &e: v) cin >> e;
		solve(n, v);
	}
}
