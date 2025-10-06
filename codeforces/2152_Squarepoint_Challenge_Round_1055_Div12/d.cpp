#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)

typedef vector<int> vi;
typedef const vi cvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

struct vector_ele {
	int power_cnt;
	int power_sum;
	int emerg_cnt;
	int no_power_sum;

	vector_ele operator-(const vector_ele &other) {
		return {
			.power_cnt = this->power_cnt - other.power_cnt,
			.power_sum = this->power_sum - other.power_sum,
			.emerg_cnt = this->emerg_cnt - other.emerg_cnt,
			.no_power_sum = this->no_power_sum - other.no_power_sum,
		};
	}
};

void solve(cvi &v, cvpii &query) {
	const int n = v.size();

	vector<vector_ele> pref_sum(n + 1);
	pref_sum[0] = {0, 0, 0, 0};
	forn(i, n) {
		vector_ele ve = pref_sum[i];
		if (v[i] == 0) {
			ve.power_cnt += 1;
		} else {
			int temp = v[i];
			bool is_odd = temp % 2; temp >>= 1;
			int onecnt = 0, power = 0;
			while (temp > 0) {
				onecnt += temp % 2;
				power++; temp >>= 1;
			}
			if (onecnt == 1 && !is_odd) {
				ve.power_cnt += 1; ve.power_sum += power;
			} else if (onecnt == 1) {
				ve.emerg_cnt += 1; ve.no_power_sum += power;
			} else {
				ve.no_power_sum += power;
			}
		}
		pref_sum[i + 1] = ve;
	}

	// for (auto &ele: pref_sum) {
	// 	cout << ele.power_cnt << ", " << ele.power_sum << ", " << ele.emerg_cnt << ", " << ele.no_power_sum << endl;
	// }
	// cout << endl;
	// cout << endl;

	for (auto &q: query) {
		vector_ele curr = pref_sum[q.second] - pref_sum[q.first - 1];
		auto &[power_cnt, power_sum, emerg_cnt, no_power_sum] = curr;
		int last = q.second - q.first + 1 - power_cnt - emerg_cnt;
		int ans = power_sum + no_power_sum + emerg_cnt / 2 + last; 
		cout << ans << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(tc, t) {
		int n, q; cin >> n >> q;
		vector<int> v(n); for (auto &e: v) cin >> e;
		vector<pii> query(q); for (auto &qele: query) {
			cin >> qele.first >> qele.second;
		}
		solve(v, query);
	}
}
