#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

constexpr int INF = 1e9;

void solve(int k, vector<tuple<int, int, int>> &probe) {
	// Sum[y] - Sum[x - 1] = r
	// Sum[y] - Sum[x - 1] <= r
	// Sum[x - 1] - Sum[y] <= -r

	// 0 <= Sum[x] - Sum[x - 1] <= 1
	// Sum[x] - Sum[x - 1] <= 1
	// Sum[x - 1] - Sum[x] <= 0

	vector<vector<pair<int, int>>> adj(k + 1);

	// Sum[x] - Sum[x - 1] <= 1
	// Sum[x - 1] - Sum[x] <= 0
	for (int i = 1; i < k + 1; i++) {
		adj[i - 1].push_back({i, 1});
		adj[i].push_back({i - 1,  0});
	}

	// Sum[y] - Sum[x - 1] <= r
	// Sum[x - 1] - Sum[y] <= -r
	for (auto &[x, y, r]: probe) {
		adj[x - 1].push_back({y, r});
		adj[y].push_back({x - 1, -r});
	}

	vector<int> dist(k + 1, 0);
	for (int _i = 0; _i < k + 1; _i++) {
		for (int i = 0; i < adj.size(); i++) {
			auto &a = adj[i];
			for (auto &e: a) {
				if (dist[e.first] > e.second + dist[i]) {
					dist[e.first] = e.second + dist[i];
				}
			}
		}
	}

	for (int i = 0; i < adj.size(); i++) {
		auto &a = adj[i];
		for (auto &e: a) {
			if (dist[e.first] > e.second + dist[i]) {
				cout << "NONE"; return;
			}
		}
	}

	for (int i = 1; i < dist.size(); i++) {
		if (dist[i] == dist[i - 1] + 1) {
			cout << "#";
		} else {
			cout << "-";
		}
	}
	// for (auto &d: dist) {
	// 	cout << d << " ";
	// } cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int k, n; cin >> k >> n;
	vector<tuple<int, int, int>> probe;
	for (int i = 0; i < n; i++) {
		int x, y, r; cin >> x >> y >> r;

		probe.push_back({x, y, r});
	}
	solve(k, probe);
}
