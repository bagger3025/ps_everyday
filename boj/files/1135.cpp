#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

using namespace std;

int get_time(const vector<vector<int>> &adj, int idx) {
	int ret = 0;
	vector<int> times;
	for (auto &y: adj[idx]) {
		times.push_back(get_time(adj, y));
	}
	sort(times.rbegin(), times.rend());
	for (int i = 0; i < times.size(); i++) {
		ret = max(ret, times[i] + i + 1);
	}
	return ret;
}

void solve(vector<int> &v) {
	const int n = v.size();
	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		adj[v[i]].push_back(i);
	}

	cout << get_time(adj, 0);
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	solve(v);
}
