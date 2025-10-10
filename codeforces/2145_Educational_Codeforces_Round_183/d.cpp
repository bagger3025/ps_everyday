#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define all(x) x.begin(), x.end()

typedef const int cint;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

#define MAX_DP (450 + 10)

pii dp[MAX_DP];

void solve(int n, int k) {
	int no_conversion = n * (n - 1) / 2 - k;
	if (dp[no_conversion].first > n) {
		cout << "0\n"; return;
	}
	vector<int> ans; ans.reserve(n);

	while (no_conversion > 0) {
		int cnt = dp[no_conversion].second;
		for (int i = n - cnt + 1; i <= n; i++) {
			cout << i << " ";
		}
		n -= cnt;
		no_conversion -= cnt * (cnt - 1) / 2;
	}
	while (n >= 1) {
		cout << n << " ";
		n--;
	}
	cout << "\n";
}

void cal_dp() {
	vector<int> v(32);
	int val = 0;
	for (int i = 1; i <= v.size(); i++) {
		val += i; v[i - 1] = val;
	}

	dp[1] = {2, 2};
	int p = 1;
	for (int i = 2; i < MAX_DP; i++) {
		if (i == v[p]) {
			dp[i] = {p + 2, p + 2}; p++;
			continue;
		}
		dp[i] = {dp[i - v[p - 1]].first + p + 1, p + 1};
		for (int j = p - 2; j >= 0; j--) {
			if (dp[i - v[j]].first + j + 1 < dp[i].first) {
				dp[i] = {dp[i - v[j]].first + j + 2, j + 2};
			}
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cal_dp();
	// for (int i = 1; i < MAX_DP; i++) {
	// 	cout << i << " = {" << dp[i].first << ", " << dp[i].second << "} " << endl;
	// }
	// cout << endl;

	int t; cin >> t;
	forn(_t, t) {
		int n, k; cin >> n >> k;
		solve(n, k);
	}
}
