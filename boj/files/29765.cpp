#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct ele {
	int query;
	int from; int to; int x;
};

bool bellman_ford(const vector<vector<pair<int, int>>> &adj, vector<int> &dist) {
	const int v = dist.size();
	for (int i = 0; i < v; i++) {
		for (int from = 0; from < v; from++) {
			for (auto &[to, w]: adj[from]) {
				if (dist[to] > dist[from] + w) {
					dist[to] = dist[from] + w;
				}
			}
		}
	}

	for (int from = 0; from < v; from++) {
		for (auto &[to, w]: adj[from]) {
			if (dist[to] > dist[from] + w) {
				return false;
			}
		}
	}
	return true;
}

void solve(int n, const vector<ele> &ps) {
	vector<vector<vector<pair<int, int>>>> adj(31, vector<vector<pair<int, int>>>(n + 1));

	for (auto [q, a, b, x]: ps) {
		if (q == 1) {
			for (int i = 0; i < 31; i++) {
				if (x % 2) {
					// A_b - A_{a - 1} = b - a + 1
					adj[i][a - 1].push_back({b, b - a + 1});
					// cout << "i, from = " << i << ", " << a - 1 << " => " << b << ", " << b - a + 1 << endl;
					adj[i][b].push_back({a - 1, -b + a - 1});
					// cout << "i, from = " << i << ", " << b << " => " << a << ", " << -b + a - 1 << endl;
				} else {
					// A_b - A_{a - 1} <= b - a
					adj[i][a - 1].push_back({b, b - a});
				}
				x /= 2;
			}
		} else {
			for (int i = 0; i < 31; i++) {
				if (x % 2) {
					// A_b - A_{a - 1} >= 1
					adj[i][b].push_back({a - 1, -1});
				} else {
					// A_b - A_{a - 1} = 0
					adj[i][a - 1].push_back({b, 0});
					adj[i][b].push_back({a - 1, 0});
				}
				x /= 2;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 31; j++) {
			adj[j][i - 1].push_back({i, 1});
			adj[j][i].push_back({i - 1, 0});
		}
	}

	vector<vector<int>> dist(31, vector<int>(1 + n, 0));
	for (int i = 0; i < 31; i++) {
		bool ret = bellman_ford(adj[i], dist[i]);
		if (!ret) {
			cout << -1; return;
		}
	}

	vector<int> ans(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 30; j >= 0; j--) {
			ans[i] = ans[i] * 2 + (dist[j][i + 1] != dist[j][i]);
		}
	}

	for (auto &a: ans) {
		cout << a << " ";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, p; cin >> n >> p;
	vector<ele> ps;
	for (int i = 0; i < p; i++) {
		int q, a, b, x; cin >> q >> a >> b >> x;
		ps.push_back({q, a, b, x});
	}
	solve(n, ps);

}
