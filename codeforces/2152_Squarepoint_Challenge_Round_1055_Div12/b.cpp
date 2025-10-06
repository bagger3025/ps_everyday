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

void solve(int n, int rk, int ck, int rd, int cd) {
	int xmax, ymax;
	if (rk == rd) {
		ymax = 0;
	} else if (rk > rd) {
		ymax = (rk - rd) + (n - rk);
	} else {
		ymax = (rd - rk) + rk;
	}

	if (ck == cd) {
		xmax = 0;
	} else if (ck > cd) {
		xmax = (ck - cd) + n - ck;
	} else {
		xmax = (cd - ck) + ck;
	}

	cout << max(ymax, xmax) << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(tc, t) {
		int n, rk, ck, rd, cd; cin >> n >> rk >> ck >> rd >> cd;
		solve(n, rk, ck, rd, cd);

	}
}
