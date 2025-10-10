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

typedef long long ll; typedef vector<ll> vll; typedef vector<vll> vvll;
typedef const ll cll; typedef const vll cvll; typedef const vvll cvvll;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

inline bool is_safe(cll &val, cll &a, cll &b) {
	return val % a != b;
}

#define POS_LEN 2520

void solve(int n, ll m, cvi &as, cvi &bs) {

	vector<pii> pos(POS_LEN, {-1, -1});
	pos[0] = {0, 0};
	ll cur_pos = 0, moves = 0;
	while (true) {
		for (int i = 0; i < n; i++, moves++) {
			if (is_safe(cur_pos + 1, as[i], bs[i])) {
				cur_pos += 1;
			} 
			if (cur_pos == m) {
				cout << moves + 1 << "\n"; return;
			}
		}
		if (pos[cur_pos % POS_LEN].first == -1) {
			pos[cur_pos % POS_LEN] = {cur_pos, moves};
			// cout << "pos[" << cur_pos % 210 << "] = " << cur_pos << ", " << moves << endl;
		} else {
			break;
		}
	}

	ll period = moves - pos[cur_pos % POS_LEN].second;
	ll pos_amount = cur_pos - pos[cur_pos % POS_LEN].first;
	if (pos_amount == 0) {
		cout << "-1\n"; return;
	}
	// cout << "period = " << period << endl;
	// cout << "amount = " << pos_amount << endl;

	ll times = (m - cur_pos) / pos_amount;
	// cout << "times = " << times << endl;

	moves += period * times;
	cur_pos += pos_amount * times;

	if (cur_pos == m) {
		cout << moves << "\n"; return;
	}

	// cout << "moves = " << moves << ", cur_pos = " << cur_pos << ", m = " << m << endl;
	while (true) {
		for (int i = 0; i < n; i++, moves++) {
			if (is_safe(cur_pos + 1, as[i], bs[i])) {
				cur_pos++;
			}
			if (cur_pos == m) {
				cout << moves + 1 << "\n"; return;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		ll n, m; cin >> n >> m;
		vi as(n), bs(n);
		for (auto &a: as) cin >> a;
		for (auto &b: bs) cin >> b;

		solve(n, m, as, bs);
	}
}
