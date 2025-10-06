#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define all(x) x.begin(), x.end()

typedef const int cint;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

int get_parlen(int n) {
	int len = 1;
	while ((1 << len) < n) {
		len++;
	}
	return len;
}

int uplevel(cvvi &par, int node, int l) {
	for (int i = 0; l != 0; i++) {
		if (!(l & (1 << i))) continue;

		node = par[node][i];
		
		l -= 1 << i;
	}
	return node;
}

pair<int, int> get_lca(cvvi &par, cint &parlen, cvi &level, int v, int u) {
	int vlvl = level[v], ulvl = level[u];
	int ret_node = 0;
	if (vlvl > ulvl) {
		v = uplevel(par, v, vlvl - ulvl);
		ret_node = vlvl - ulvl;
	} else if (ulvl > vlvl){
		u = uplevel(par, u, ulvl - vlvl);
		ret_node = ulvl - vlvl;
	}

	if (v == u) return {v, ret_node};

	for (int p = parlen - 1; p >= 0; p--) {
		if (par[u][p] != par[v][p]) {
			u = par[u][p];
			v = par[v][p];
			ret_node += (1 << p) * 2;
		}
	}
	return {par[u][0], ret_node + 2};
}

void solve(int z, cvi &v, cvpii &qry) {
	const int n = v.size();
	const int parlen = get_parlen(n);
	// cout << "parlen: " << parlen << endl;

	vector<int> level(n);
	vector<vector<int>> par(n, vector<int>(parlen));
	for (int lp = 0, rp = 0; lp < v.size(); lp++) {
		while (rp < n && v[rp] <= v[lp] + z) rp++;
		par[lp][0] = rp == n ? -1 : rp;
	}

	for (int i = n - 1; i >= 0; i--) {
		if (par[i][0] == -1) level[i] = 1;
		else level[i] = 1 + level[par[i][0]];
	}

	// cout << "level: ";
	// for (auto &l: level) {
	// 	cout << l << " ";
	// } cout << endl;

	for (int j = 1; j < parlen; j++) {
		for (int i = 0; i < n; i++) {
			if (par[i][j - 1] != -1) {
				par[i][j] = par[par[i][j - 1]][j - 1];
			} else {
				par[i][j] = -1;
			}
		}
	}

	// cout << "par: ";
	// for (auto &p: par) {
	// 	for (auto &e: p) {
	// 		cout << e << "-";
	// 	} cout << " / ";
	// } cout << endl;

	vector<vector<pair<int, int>>> lca_par(n, vector<pair<int, int>>(parlen));
	for (int i = 0; i < n - 1; i++) {
		lca_par[i][0] = get_lca(par, parlen, level, i, i + 1);
	}
	lca_par[n - 1][0] = {-1, -1};

	// cout << "lca_par: ";
	// for (auto &lele: lca_par) {
	// 	cout << "{" << lele[0].first << ", " << lele[0].second << "} ";
	// } cout << endl;

	for (int p = 1; p < parlen; p++) {
		for (int i = 0; i < n; i++) {
			auto &[first_par, first_nodes] = lca_par[i][p - 1];
			if (first_par == -1) {
				lca_par[i][p] = {-1, -1};
			} else {
				lca_par[i][p] = lca_par[first_par][p - 1];
				lca_par[i][p].second += first_nodes;
			}
		}
	}

	for (auto [l, r]: qry) {
		if (r - l + 1 <= 2) {
			cout << r - l + 1 << endl; continue;
		}
		l--;
		int nodes = 2;

		for (int p = parlen - 1; p >= 0; p--) {
			if (lca_par[l][p].first == -1 || lca_par[l][p].first >= r) continue;
			nodes += lca_par[l][p].second;
			// cout << "nodes += lca_par[" << l << "][" << p << "].second" << endl;
			l = lca_par[l][p].first;
		}
		int p1 = l, p2 = l + 1;
		if (p2 < r) {
			for (int p = parlen - 1; p >= 0; p--) {
				if (par[p1][p] != -1 && par[p1][p] < r) {
					p1 = par[p1][p];
					nodes += (1 << p);
					// cout << "nodes += 1 << " << p << endl;
				}
				if (par[p2][p] != -1 && par[p2][p] < r) {
					p2 = par[p2][p];
					nodes += (1 << p);
					// cout << "nodes += 1 << " << p << endl;
				}
			}
		} else {
			nodes--;
			// cout << "nodes -= 1" << endl;
		}
		// cout << "p1 = " << p1 << ", p2 = " << p2 << ", " << nodes << endl;
		cout << nodes << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n, z; cin >> n >> z;
		vi v(n); for (int &e: v) cin >> e;
		int qn; cin >> qn;
		vpii qry(qn); for (auto &q: qry) cin >> q.first >> q.second;
		solve(z, v, qry);
	}
}
