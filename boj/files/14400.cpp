#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long find_mid(vector<int> &v) {
	const int n = v.size();

	sort(v.begin(), v.end());
	int midval;
	if (n % 2) {
		midval = v[n / 2];
	} else {
		midval = (v[n / 2] + v[n / 2 - 1]) / 2;
	}

	long long ret = 0;
	for (auto &e: v) {
		ret += e - midval > 0 ? e - midval : midval - e;
	}
	return ret;
}

void solve(vector<int> &xs, vector<int> &ys) {
	cout << find_mid(xs) + find_mid(ys);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	vector<int> xs(n), ys(n);
	for (int i = 0; i < n; i++) {
		cin >> xs[i] >> ys[i];
	}
	solve(xs, ys);
}
