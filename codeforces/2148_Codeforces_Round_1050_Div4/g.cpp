#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct pq_ele {
	int idx;
	int val;

	bool operator<(const pq_ele &other) const {
		return this->val < other.val;
	}
};

void insert_pq(vector<int> &dp, int idx, priority_queue<pq_ele> &pq) {
	dp[idx]++;
	pq.push({idx, dp[idx]});
}

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<int> dp(n + 1, 0);
	priority_queue<pq_ele> pq;

	int maxval = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 2; j * j <= a[i]; j++) {
			if (a[i] % j != 0) continue;

			insert_pq(dp, j, pq);
			if (j * j != a[i]) {
				insert_pq(dp, a[i] / j, pq);
			}
		}

		if (a[i] != 1) {
			insert_pq(dp, a[i], pq);
		}

		priority_queue<pq_ele> pq_temp;
		while (!pq.empty() && pq.top().val == i + 1) {
			pq_temp.push(pq.top());
			pq.pop();
		}
		while (!pq.empty()) {
			auto t = pq.top();
			if (dp[t.idx] == t.val) break;
			pq.pop();
		}
		if (pq.empty()) maxval = 0;
		else {
			maxval = pq.top().val;
			pq_temp.push(pq.top());
		}

		pq.swap(pq_temp);

		cout << maxval << " ";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	for (int tc = 0; tc < t; tc++) {
		solve();
	}
}
