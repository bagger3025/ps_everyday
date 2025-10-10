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


void solve(int n, int k, const string &s) {
	int zeros = 0, ones = 0;
	for (auto &c: s) {
		if (c == '0') zeros++;
		else if (c == '1') ones++;
	}
	int twos = k - zeros - ones;
	int lefts = n - zeros - ones;
	forn(i, zeros) {
		cout << "-";
	}
	if (lefts == twos) {
		forn(i, lefts) {
			cout << "-";
		}
	} else if (lefts < twos * 2) {
		forn(i, lefts) {
			cout << "?";
		}
	} else {
		lefts -= twos * 2;
		forn(i, twos) {
			cout << "?";
		}
		forn(i, lefts) {
			cout << "+";
		}
		forn(i, twos) {
			cout << "?";
		}
	}
	forn(i, ones) {
		cout << "-";
	}
	cout << "\n";
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n, k; cin >> n >> k;
		string s; cin >> s;
		solve(n, k, s);
	}
}
