#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// const int MOD = 998244353;

typedef long long ll; typedef vector<ll> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi; typedef vector<vvi> vvvi;
typedef const int cint; typedef const vi cvi; typedef const vvi cvvi; typedef const vvvi cvvvi;

typedef vector<string> vs;
typedef const vs cvs;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

typedef pair<ll, ll> pll; typedef vector<pll> vpll;
typedef const pll cpll; typedef const vpll cvpll;

typedef const string cstr;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define all(x) (x).begin(), (x).end()

void solve(vi &v, cvpii &queries) {
	for (auto [l, r]: queries) {
		l--;
		int target_cnt = (r - l) / 3 + 1;
		vi ret;

		vi new_arr(v.begin() + l, v.begin() + r);
		sort(all(new_arr));

		for (int lp = 0, rp = 0; lp < new_arr.size(); lp = rp) {
			while (rp < new_arr.size() && new_arr[rp] == new_arr[lp]) rp++;
			if (rp - lp >= target_cnt) ret.push_back(new_arr[lp]);
		}

		if (ret.size() == 0) {
			cout << "-1\n";
		} else {
			sort(all(ret));
			for (auto &r: ret) {
				cout << r << " ";
			}
			cout << endl;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(i, t) {
		int n, q; cin >> n >> q;
		vi v(n); for (auto &ele: v) cin >> ele;
		vpii queries(q); for (auto &qele: queries) cin >> qele.first >> qele.second;
		solve(v, queries);
	}

	return 0;
}

