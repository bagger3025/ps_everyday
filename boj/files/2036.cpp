#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(vector<long long> &v) {
	const int n = v.size();

	sort(v.begin(), v.end());
	
	long long ans = 0;
	int p = 0;
	while (p + 1 < v.size() && v[p] < 0 && v[p + 1] < 0) {
		ans += v[p] * v[p + 1]; p += 2;
	}
	if (p == v.size()) {
		cout << ans; return;
	} else if (p + 1 == v.size()) {
		cout << ans + v[p]; return;
	}

	if (v[p] < 0) {
		if (v[p + 1] == 0) {
			ans += 0; p += 2;
		} else if (v[p + 1] > 0) {
			ans += v[p]; p += 1;
		}
	}

	while (p < v.size() && v[p] <= 1) {
		ans += v[p]; p++;
	}

	int i;
	for (i = v.size() - 1; i - 1 >= p; i -= 2) {
		ans += v[i] * v[i - 1];
	}
	if (i == p) {
		ans += v[i];
	}

	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	vector<long long> v(n); for (auto &e: v) cin >> e;
	solve(v);
}
