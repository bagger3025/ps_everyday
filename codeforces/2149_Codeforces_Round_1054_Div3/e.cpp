#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>

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

struct pq_ele {
	int num;
	int idx;

	bool operator<(const pq_ele &other) const {
		return this->idx < other.idx;
	}
	bool operator>(const pq_ele &other) const {
		return this->idx > other.idx;
	}
};

void solve(int n, int k, int l, int r, cvi &v) {
	map<int, vi> next_ele;
	for (int i = n - 1; i >= 0; i--) {
		next_ele[v[i]].push_back(i);
	}

	// min heap
	priority_queue<pq_ele, vector<pq_ele>, greater<>> pq;

	for (auto &ue: next_ele) {
		pq.push({.num=ue.first, .idx=ue.second.back()});
		ue.second.pop_back();
	}

	map<int, int> idx_list;
	for (int i = 0; i < k; i++) {
		if (pq.empty()) {
			cout << "0\n"; return;
		}
		auto t = pq.top(); pq.pop();
		idx_list[t.idx] = t.num;
	}
	
	long long ans = 0;
	while (idx_list.size() == k) {
		auto begin = idx_list.begin();

		int lp = begin->first, rp = idx_list.rbegin()->first;
		int rp2 = pq.empty() ? n : pq.top().idx;
		ll temp = min(rp2, lp + r) - max(lp + l - 1, rp);
		if (temp > 0) ans += temp;

		int num = begin->second;
		idx_list.erase(begin);
		auto it = next_ele.find(num);
		if (it->second.size() > 0) {
			pq.push({num, it->second.back()});
			it->second.pop_back();
		} else {
			next_ele.erase(it);
		}

		if (pq.empty()) break;
		auto t = pq.top(); pq.pop();
		idx_list[t.idx] = t.num;
	}

	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(i, t) {
		int n, k, l, r; cin >> n >> k >> l >> r;
		vi v(n);
		forn(j, n) {
			cin >> v[j];
		}
		solve(n, k, l, r, v);
	}

	return 0;
}


