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

int do_query(int u, int v) {
	cout << u << " " << v << endl; cout.flush();
	int x; cin >> x;
	if (x == -1) exit(1);
	return x;
}

void solve(int n) {
	for (int len = 2; 1; len <<= 1) {
		for (int i = 0; i <= n / len; i++) {
			int start = i * len, mid = min(n, start + len / 2), end = min(n, start + len);
			if (mid == end) continue;
			forn(j, mid - start) forn(k, end - mid) {
				if (do_query(start + j + 1, mid + k + 1)) return;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n; cin >> n;
		solve(n);
	}
}
