#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

using namespace std;

void solve(int n, vector<pair<int, int>> &v) {
	sort(v.begin(), v.end());
	
	priority_queue<int, vector<int>, greater<>> pq;

	int ans = 0;
	for (int i = 1, p = 0; i <= n; i++) {
		while (p < v.size() && v[p].first <= i) {
			pq.push(v[p].second);
			p++;
		}
		while (!pq.empty()) {
			int t = pq.top(); pq.pop();
			if (t >= i) {
				ans++;
				break;
			}
		}
	}
	cout << ans << "\n";
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	for (int _t = 0; _t < t; _t++) {
		int n, m; cin >> n >> m;
		vector<pair<int, int>> v(m);
		for (int i = 0; i < m; i++) {
			cin >> v[i].first >> v[i].second;
		}
		
		solve(n, v);
	}
}
