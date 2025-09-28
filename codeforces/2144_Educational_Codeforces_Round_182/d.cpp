#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll; typedef vector<long long> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

// both inclusive
int get_cnt(cvi &cnt, ll from, ll to) {
	if (from >= cnt.size() || to < 0) return 0;

	to = min<long long>(cnt.size() - 1, to);
	int from_val = from <= 0 ? 0 : cnt[from - 1];

	return cnt[to] - from_val;
}

void solve() {
	ll n, y; cin >> n >> y;
	vl v(n);
	vi cnt(200'000, 0);

	ll max_v = -1;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		cnt[v[i] - 1]++;
		max_v = max(max_v, v[i]);
	}
	sort(v.begin(), v.end());
	for (int i = 1; i < cnt.size(); i++) {
		cnt[i] += cnt[i - 1];
	}

	ll ans = -y * n;
	if (max_v == 1) {
		ans = n;
	}
	for (int x = 2; x <= max_v; x++) {
		int new_print = n;
		ll cur_ans = 0;

		int target_v = (max_v + x - 1) / x;
		for (int i = 1; i <= target_v; i++) {
			ll original_cnt = get_cnt(cnt, i - 1, i - 1);
			ll converted_cnt = get_cnt(cnt, (i - 1) * x, i * x - 1);

			new_print -= min(original_cnt, converted_cnt);
			cur_ans += i * converted_cnt;
		}

		// for (int i = 0, j = 1; i < n; i = j, j = i + 1) {
		// 	while (j < n && v[i] == v[j]) {
		// 		j++;
		// 	}

		// 	int other_cnt = get_cnt(cnt, (v[i] - 1) * x, v[i] * x - 1);
		// 	new_print -= min(j - i, other_cnt);

		// 	cur_ans += (v[i] + x - 1) / x * (j - i);
		// }

		ans = max(ans, cur_ans - y * new_print);
	}
	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase; cin >> testcase;

	for (int tc = 1; tc <= testcase; tc++) {
		solve();
	}
	return 0;
}
