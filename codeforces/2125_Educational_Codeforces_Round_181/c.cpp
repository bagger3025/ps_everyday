#include <iostream>
#include <algorithm>

using namespace std;

struct vec_ele {
	int l;
	int r;
	int p;
	int q;
};

const int MOD = 998244353;

int rev_mod(int r) {
	
}

void solve() {
	int n, m; cin >> n >> m;
	vector<vec_ele> v;
	for (int i = 0; i < n; i++) {
		int l, r, p, q; cin >> l >> r >> p >> q;
		v.push_back({l, r, p, q});
	}

}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	solve();
	return 0;
}
