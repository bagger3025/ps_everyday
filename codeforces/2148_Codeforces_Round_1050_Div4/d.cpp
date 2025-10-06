#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void solve() {
	int n; cin >> n;
	priority_queue<int, vector<int>, greater<>> pq;
	long long ret = 0;
	int odds_cnt = 0;

	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		ret += t;
		if (t % 2 == 0) {
		} else {
			odds_cnt++;
			pq.push(t);
		}
	}
	for (int i = 0; i < odds_cnt / 2; i++) {
		ret -= pq.top(); pq.pop();
	}

	if (odds_cnt == 0) {
		cout << 0 << endl;
	} else {
		cout << ret << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	for (int tc = 0; tc < t; tc++) {
		solve();
	}
}
