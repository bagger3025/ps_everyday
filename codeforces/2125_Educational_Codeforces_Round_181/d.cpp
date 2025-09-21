#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct vec_ele {
	int l;
	int r;
	long long prob;
};

const int MOD = 998244353;

// n = qa + p
// na^(-1) = q + pa^(-1)
// -q = pa^(-1)
// -qp^(-1) = a^(-1)
long long rev_mod(long long r) {
	if (r == 0) return 0;
	if (r == 1) return 1;
	long long q = MOD / r;
	long long p = MOD % r;
	return ((-q * rev_mod(p)) % MOD + MOD) % MOD;
}

bool v_compare(const vec_ele &a, const vec_ele &b) {
	return a.l < b.l;
}

struct map_ele {
	int idx;
	long long prob;
};

void upgrade_map(map_ele &mele, int idx, const vector<long long> &notSelected) {
	if (idx < 0) return;
	if (mele.prob == 0) {
		mele.idx = idx;
		return;
	}
	long long untilprob = idx < 0 ? 1 : notSelected[idx];
	long long fromprob = mele.idx < 0 ? 1 : notSelected[mele.idx];
	long long prob = (untilprob * rev_mod(fromprob)) % MOD;
	mele = {idx, (mele.prob * prob) % MOD};
}

void solve() {
	int n, m; cin >> n >> m;
	vector<vec_ele> v;
	v.reserve(n);
	for (int i = 0; i < n; i++) {
		int l, r, p, q; cin >> l >> r >> p >> q;
		v.push_back({l, r, ((long long)p * rev_mod(q)) % MOD});
	}

	sort(v.begin(), v.end(), v_compare);

	vector<long long> notSelected(n);
	long long t = 1;
	for (int i = 0; i < n; i++) {
		t = (t * (MOD + 1 - v[i].prob)) % MOD;
		notSelected[i] = t;
	}

	vector<map_ele> mdp(m + 1, {-1, 0});
	mdp[0] = {-1, 1};
	for (int i = 0; i < n; i++) {
		map_ele &lele = mdp[v[i].l - 1];
		if (lele.prob == 0) continue;
		upgrade_map(lele, i - 1, notSelected);

		long long curprob = (lele.prob * v[i].prob) % MOD;
		upgrade_map(mdp[v[i].r], i, notSelected);
		mdp[v[i].r].prob = (mdp[v[i].r].prob + curprob) % MOD;
	}
	upgrade_map(mdp[m], n - 1, notSelected);
	cout << mdp[m].prob;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	solve();
	return 0;
}
