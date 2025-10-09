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

void solve(int n) {
	int winners = n, losers = 0;
	int ans = 0;
	while (winners > 1) {
		ans += winners / 2 + losers / 2;
		losers -= losers / 2;
		losers += winners / 2;
		winners -= winners / 2;
	}
	while (losers > 1) {
		ans += losers / 2;
		losers -= losers / 2;
	}
	cout << ans + 1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n; cin >> n;
		solve(n);
	}
}
