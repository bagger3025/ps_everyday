#include <cassert>
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


inline int get_val(char ch, int aval, int bval) {
	return ch == 'a' ? aval : bval;
}

void solve(int n, const string &s) {
	int val = 0;
	int aval = 1, bval = -1;
	for (auto &c: s) {
		if (c == 'a') val += aval;
		else val += bval;
	}

	if (val == 0) {
		cout << "0\n"; return;
	} else if (val == n || val == -n) {
		cout << "-1\n"; return;
	}

	if (val < 0) {
		val = -val; swap(aval, bval);
	}

	int t = n;
	vi pointers(2 * n, -1);

	int ans = n;
	for (int p = 0; p < n; p++) {
		pointers[t] = p;
		// cout << "pointers[" << t << "] <- " << p << endl;
		t += get_val(s[p], aval, bval);

		if (pointers[t - val] != -1) {
			ans = min(ans, p + 1 - pointers[t - val]);
		}
	}
	
	if (ans == n) ans = -1;

	cout << ans << "\n";
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n; cin >> n;
		string s; cin >> s;
		solve(n, s);
	}
}
