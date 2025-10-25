#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct edge {
	int from;
	int to;
	int weight;
};

constexpr int INF = 21e8;

void solve(vector<edge> &edges, int n, int s) {
	vector<int> dist(n, INF), par(n, -1);
	dist[s] = 0; par[s] = s;

	int node;
	for (int i = 0; i < n; i++) {
		node = -1;
		for (auto &[x, y, w]: edges) {
			if (dist[y] > dist[x] + w) {
				dist[y] = dist[x] + w;
				par[y] = x;
				node = y;
			}
		}
	}

	if (node == -1) {
		// No negative cycle
		cout << "PATH\n";
		for (auto &d: dist) {
			cout << d << " ";
		}
	} else {
		cout << "CYCLE\n";
		for (int i = 0; i < n; i++) {
			node = par[node];
		}

		vector<int> cycles;
		for (int v = node; v != node || cycles.size() < 1; v = par[v]) {
			cycles.push_back(v);
		}
		cycles.push_back(node);
		reverse(cycles.begin(), cycles.end());
		cout << cycles.size() - 1 << "\n";
		for (auto &c: cycles) {
			cout << c << " ";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m, s; cin >> n >> m >> s;
	vector<edge> edges;
	for (int i = 0; i < m; i++) {
		int a, b, c; cin >> a >> b >> c;
		edges.push_back({a, b, c});
	}
	solve(edges, n, s);
}
