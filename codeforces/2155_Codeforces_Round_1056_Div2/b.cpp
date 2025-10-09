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

void solve(int n, int k) {
	if (n * n - 1 == k) {
		cout << "NO\n"; return;
	}

	k = n * n - k;
	if (k == 0) {
		cout << "YES\n";
		forn(i, n) {
			forn(j, n) {
				cout << "R";
			} cout << "\n";
		}
		return;
	}

	cout << "YES\n";
	forn(i, n) {
		if (k >= 2) {cout << "RL"; k -= 2;}
		else if (k == 1) {cout << "UR"; k -= 1;}
		else cout << "RR";
		forn(j, n - 2) {
			if (k > 0) {cout << "L"; k--;}
			else {cout << "R";}
		} cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n, k; cin >> n >> k;
		solve(n, k);
	}
}
