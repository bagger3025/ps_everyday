#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

void solve(vector<int> &v, long long b, long long c) {
	if (c >= b) {
		long long ans = 0;
		for (auto &e: v) {
			ans += e;
		}
		cout << ans * b;
		return;
	}
	const int n = v.size();
	long long ans = 0;
	long long prev_two = 0, prev_one = 0;
	for (int i = 0; i < n; i++) {
		long long t = v[i];

		long long next_two = min(t, prev_one);
		prev_one -= next_two;
		t -= next_two;

		long long next_three = min(t, prev_two);
		prev_two -= next_three;
		t -= next_three;

		long long next_one = t;

		ans += next_three * (b + c * 2);
		ans += prev_two * (b + c);
		ans += prev_one * b;

		prev_two = next_two;
		prev_one = next_one;
	}

	ans += prev_two * (b + c);
	ans += prev_one * b;
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	long long n, b, c; cin >> n >> b >> c;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	solve(v, b, c);
}
