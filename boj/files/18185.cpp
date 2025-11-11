#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

void solve(vector<int> &v) {
	const int n = v.size();
	long long ans = 0;
	int prev_two = 0, prev_one = 0;
	for (int i = 0; i < n; i++) {
		int t = v[i];

		int next_two = min(t, prev_one);
		prev_one -= next_two;
		t -= next_two;

		int next_three = min(t, prev_two);
		prev_two -= next_three;
		t -= next_three;

		int next_one = t;

		ans += next_three * 7;
		ans += prev_two * 5;
		ans += prev_one * 3;

		prev_two = next_two;
		prev_one = next_one;
	}

	ans += prev_two * 5;
	ans += prev_one * 3;
	cout << ans;
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
