#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

const long long LONG_INF = 1e18L;
const int INF = 1e9;

struct pq_ele {
	int node;
	long long price;
	int low_oil;

	bool operator<(const pq_ele &other) const {
		if (price != other.price) return this->price > other.price;
		return this->low_oil > other.low_oil;
	}
};


void solve(const vector<int> &oils, const vector<vector<pair<int, int>>> &adj) {
	const int n = oils.size();

	priority_queue<pq_ele> pq;
	vector<int> visited(n, INF);
	pq.push({0, 0, oils[0]});

	while (!pq.empty()) {
		auto t = pq.top(); pq.pop();
		if (t.low_oil >= visited[t.node]) continue;
		if (t.node == n - 1) {
			cout << t.price << "\n";
			return;
		}

		visited[t.node] = t.low_oil;

		for (auto &[y, len]: adj[t.node]) {
			int w = min(t.low_oil, oils[y]);
			if (w >= visited[y]) continue;

			long long price = t.price + len * t.low_oil;
			pq.push({y, price, w});
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m; cin >> n >> m;
	vector<int> oils(n); for (int &e: oils) cin >> e;
	vector<vector<pair<int, int>>> adj(n);
	for (int i = 0; i < m; i++) {
		int u, v, w; cin >> u >> v >> w; u--; v--;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	
	solve(oils, adj);

}
