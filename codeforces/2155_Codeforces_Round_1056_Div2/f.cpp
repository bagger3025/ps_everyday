#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define all(x) x.begin(), x.end()

typedef const int cint;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii; typedef vector<vpii> vvpii;
typedef const pii cpii; typedef const vpii cvpii; typedef const vvpii cvvpii;

typedef vector<bool> vb;
typedef const vb cvb;

int n, k, s, q;

void get_dset(cvvi &adj, vvi &c) {
	vector<bool> visited(n, false);
	vvpii temp(n);
	vpii pars(k, {-1, -1});

	stack<pii> st;
	st.push({0, 0});

	int global_int = 0;

	while (!st.empty()) {
		auto [v, par] = st.top();
		if (visited[v]) {
			st.pop();
			forn(i, c[v].size()) {
				auto &vc = c[v][i];
				auto t = pars[vc];
				pars[vc] = temp[v][i];
				vc = t.second;
			}
			continue;
		}
		visited[v] = true;

		temp[v].resize(c[v].size());
		forn(i, c[v].size()) {
			auto &vc = c[v][i];
			int vc_int;
			if (pars[vc].first != par) {
				vc_int = global_int++;
			} else {
				vc_int = pars[vc].second;
			}

			temp[v][i] = pars[vc];
			pars[vc] = {v, vc_int};
		}

		for (auto &y: adj[v]) {
			if (visited[y]) continue;
			st.push({y, v});
		}
	}
}

void solve(cvvi &adj, vvi &c, vpii &qry) {
	get_dset(adj, c);

	vpii qry_sorted(q);
	forn(i, q) {
		auto &[start, end] = qry[i];
		if (c[start].size() < c[end].size()) swap(start, end);
		qry_sorted[i] = {start, i};
	}
	sort(qry_sorted.begin(), qry_sorted.end());

	vi ans(q), ans_cached(n, -1), cnt(s, 0);
	forn(i, q) {
		auto &[start, _] = qry_sorted[i];
		for (auto &cele: c[start]) {
			cnt[cele]++;
		}
		// cout << "start=" << start << ": ";
		// for (auto &cele: c[start]) {
		// 	cout << cele << " ";
		// } cout << endl;

		int j;
		for (j = i; j < q && qry_sorted[j].first == start; j++) {
			auto &[_, end] = qry[qry_sorted[j].second];
			if (ans_cached[end] != -1) {
				ans[qry_sorted[j].second] = ans_cached[end]; continue;
			}

			int ans_cnt = 0;
			for (auto &cele: c[end]) {
				if (cnt[cele]) ans_cnt++;
			}
			// cout << "end=" << end << ": ";
			// for (auto &cele: c[end]) {
			// 	cout << cele << " ";
			// } cout << endl;

			ans_cached[end] = ans_cnt;
			// cout << "ans[" << qry_sorted[j].second << "] = " << ans_cnt << endl;
			ans[qry_sorted[j].second] = ans_cnt;
		}
		for (int k = i; k < j; k++) {
			ans_cached[qry[qry_sorted[k].second].second] = -1;
		}

		for (auto &cele: c[start]) {
			cnt[cele]--;
		}
		i = j - 1;
	}

	forn(i, q) {
		cout << ans[i] << " ";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		cin >> n >> k >> s >> q;
		vvi adj(n), c(n);
		vpii qry(q);

		forn(i, n - 1) {
			int u, v; cin >> u >> v; u--; v--;
			adj[u].push_back(v); adj[v].push_back(u);
		}

		forn(i, s) {
			int v, x; cin >> v >> x; v--; x--;
			c[v].push_back(x);
		}
		forn(i, q) {
			cin >> qry[i].first >> qry[i].second; qry[i].first--; qry[i].second--;
		}
		solve(adj, c, qry);
	}
}
