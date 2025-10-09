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

typedef const int cint;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

const string Mimo = "Mimo";
const string Yuyu = "Yuyu";

bool comp(const pii &a, const pii &b) {
	return a.second < b.second;
}

void solve(int n, int m, vpii &coins) {
	if (n == 1) {
		int rowcnt = 0;
		for (auto &[row, col]: coins) {
			if (col == 2) {
				rowcnt++;
			}
		}
		if (rowcnt % 2 == 1) {
			cout << Mimo << "\n";
		} else {
			cout << Yuyu << "\n";
		}
		
		return;
	}

	int prevcol = -1;
	int rowcnt = 0;
	bool alleven = true;
	sort(all(coins), comp);
	for (auto &[row, col]: coins) {
		if (col == 1) continue;
		if (prevcol == col) {
			rowcnt++;
		} else {
			if (rowcnt % 2 == 1) {
				alleven = false;
				break;
			}
			prevcol = col;
			rowcnt = 1;
		}
	}
	if (rowcnt % 2 == 1) {
		alleven = false;
	}

	if (!alleven) {
		cout << Mimo << "\n";
	} else {
		cout << Yuyu << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n, m, k; cin >> n >> m >> k;
		vpii coins(k); for (auto &c: coins) cin >> c.first >> c.second;
		solve(n, m, coins);
	}
}
