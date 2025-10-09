#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int get_level(int n) {
	int ret = 0;
	while (n > 1) {
		n >>= 1; ret++;
	}
	return ret;
}

inline int left(int idx) {
	return idx * 2 + 1;
}

inline int right(int idx) {
	return idx * 2 + 2;
}

long long dfs(const vector<int> &v, vector<vector<long long>> &dp, int idx = 0, int level = 0) {
	bool has_child = level < dp[0].size() - 1;
	long long maxval = 0;
	if (has_child) {
		maxval = max(maxval, dfs(v, dp, left(idx), level + 1));
	}

	for (int i = 0; i <= level; i++) {
		for (int j = level; j < dp[0].size(); j++) {
			dp[i][j] = max(0LL, dp[i][j] + v[idx]);
			maxval = max(maxval, dp[i][j]);
		}
	}

	if (has_child) {
		maxval = max(maxval, dfs(v, dp, right(idx), level + 1));
	}
	return maxval;
}

void solve(const vector<int> &v, const int n) {
	int level = get_level(n + 1);
	vector<vector<long long>>dp(level, vector<long long>(level, 0));

	long long maxval = dfs(v, dp);

	if (maxval == 0) {
		maxval = v[0];
		for (long long cell: v) {
			maxval = max(maxval, cell);
		}
	}
	cout << maxval;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	vector<int> v(n); for (int &e: v) cin >> e;
	solve(v, n);
}
