#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

constexpr int INF = 0x3f3f3f3f;

void solve(int n, const vector<pair<int, int>> &bigger) {
	vector<vector<int>> adj(n, vector<int>(n, INF));

	for (auto &[x, y]: bigger) {
		adj[x][y] = 1;
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}

	int ans = 0;
	int mid = n / 2;
	for (int i = 0; i < n; i++) {
		int heavy = 0, light = 0;
		for (int j = 0; j < n; j++) {
			if (j == i) continue;
			if (adj[j][i] != INF) light++; 
			if (adj[i][j] != INF) heavy++;
		}
		if (light > mid || heavy > mid) ans++;
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m; cin >> n >> m;
	vector<pair<int, int>> bigger;
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y; x--; y--;
		bigger.push_back({x, y});
	}
	solve(n, bigger);

}
