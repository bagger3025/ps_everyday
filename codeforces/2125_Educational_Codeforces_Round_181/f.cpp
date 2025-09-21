#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// const int MOD = 998244353;

typedef long long ll; typedef vector<ll> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi;
typedef const int cint; typedef const vi cvi; typedef const vvi cvvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

typedef pair<ll, ll> pll; typedef vector<pll> vpll;
typedef const pll cpll; typedef const vpll cvpll;

typedef const string cstr;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define form(i, n, m) for (int i = int(n); i < int(m); i++)

int get_docker_cnt(cstr &s) {
	cstr docker = "docker";
	int ret = 0;

	for (int i = 0; i + 5 < s.size(); i++) {
		if (s[i] != 'd') continue;

		int j = 1;
		while (j < 6 && s[i + j] == docker[j]) j++;
		if (j == 6) ret++;
		i += j - 1;
	}
	return ret;
}

pll simulate(cvi &c, int lam) {
	cint n = c.size();

	vpll dp(n + 1);
	dp[0] = {0, 0};

	pll min_pii = dp[0];
	forn(i, n) {
		dp[i + 1] = dp[i];
		if (i + 1 - 6 >= 0) {
			// min_pii = min(min_pii, dp[i - 5]);
			dp[i + 1] = min(dp[i + 1], {dp[i - 5].first + c[i - 5] - lam, dp[i - 5].second + 1});
		}
	}
	// cout << "lam = " << lam << ": ";
	// for (auto &d: dp) {
	// 	cout << "{" << d.first << ", " << d.second << "} ";
	// } cout << endl;

	return {dp[n].second, dp[n].first};
}

ll binary_dp(cvi &c, int k, int rp) {
	// cout << "k = " << k << ", rp = " << rp << endl;
	int lp = 1;
	ll ret = -1;

	while (lp < rp) {
		ll mid = (lp + rp) / 2;

		auto [sim_k, sim_dp]= simulate(c, mid);

		// @l(x - k') + dp[k']
		// Given: dp[k'] - @lk'
		ret = max(ret, sim_dp + mid * k);
		// cout << "ret = " << ret << endl;
		// cout << "sim_k = " << sim_k << endl; cout << endl;

		if (sim_k > k) {
			rp = mid;
		} else {
			lp = mid + 1;
		}
	}
	
	return ret;
}

int get_sidx(char c) {
	switch (c) {
		case 'd': return 0;
		case 'o': return 1;
		case 'c': return 2;
		case 'k': return 3;
		case 'e': return 4;
		case 'r': return 5;
		default: return -1;
	}
}

pii get_lesseq_greater_v(cvpii &v, int max_docker_cnt, int docker_cnt) {
	vpii cnt; cnt.reserve(v.size() * 2);
	for (auto &ve: v) {
		if (ve.first <= max_docker_cnt) {
			cnt.push_back({ve.first, 1});
		}
		if (ve.second + 1 <= max_docker_cnt) {
			cnt.push_back({ve.second + 1, -1});
		}
	}
	sort(cnt.begin(), cnt.end());

	int lesseq_v = -1, greater_v = -1;
	int cntval = 0, maxval = 0, from_v = -1;
	for (auto &ve: cnt) {
		if (ve.second == -1) {
			if (cntval == maxval) {
				int cur_v = ve.first - 1;
				if (cur_v <= docker_cnt) {
					lesseq_v = cur_v;
				} else if (from_v <= docker_cnt) {
					lesseq_v = docker_cnt;
					greater_v = docker_cnt + 1;
				}
				from_v = -1;
			}
			cntval--;
		} else {
			cntval++;
			if (cntval < maxval) continue;
			if (cntval > maxval) {
				maxval = cntval;
				from_v = ve.first;

				if (ve.first <= docker_cnt) {
					lesseq_v = ve.first;
				} else if (ve.first <= max_docker_cnt) {
					lesseq_v = -1;
					greater_v = ve.first;
				} else {
					// ignore
				}
			} else {
				from_v = ve.first;
				if (ve.first <= docker_cnt) {
					lesseq_v = ve.first;
				} else if (ve.first <= max_docker_cnt) {
					if (greater_v == -1) greater_v = ve.first;
				}
			}
		}
	}
	if (from_v != -1) {
		int cur_v = max_docker_cnt;
		if (cur_v <= docker_cnt) {
			lesseq_v = cur_v;
		} else if (from_v <= docker_cnt) {
			lesseq_v = docker_cnt;
			greater_v = docker_cnt + 1;
		}
	}
	return {lesseq_v, greater_v};
}

void construct_c(vi &c, cstr &s) {
	const int n = s.size();

	forn(i, n) {
		int sidx = get_sidx(s[i]);
		if (sidx == -1) continue;
		if (i - sidx >= 0) {
			c[i - sidx]++;
		}
	}
	forn(i, n) {
		c[i] = 6 - c[i];
	}
}

void solve(cstr &s, cint &n, cvpii &v) {
	int docker_cnt = get_docker_cnt(s);
	auto [lesseq_v, greater_v] = get_lesseq_greater_v(v, s.size() / 6, docker_cnt);

	if (lesseq_v == docker_cnt || (lesseq_v == -1 && greater_v == -1)) {
		cout << "0\n";
		return;
	}
	// cout << "lesseq_v = " << lesseq_v << ", greater_v = " << greater_v << endl;

	vi c(s.size(), 0); construct_c(c, s);
	// for (auto &cc: c) {
	// 	cout << cc << " ";
	// } cout << endl;

	ll ans = s.size();
	if (lesseq_v != -1) {
		ans = docker_cnt - lesseq_v;
	}
	if (greater_v != -1) {
		ans = min(ans, binary_dp(c, greater_v, s.size() + 1));
	}
	cout << ans << "\n";
}

int naive_dp(cvi &c, int &k) {
	const int n = c.size();

	vvi dp(n + 1, vi(k + 1, 1e9));
	forn(i, n + 1) {
		dp[i][0] = 0;
	}

	form(i, 1, n + 1) { form(j, 1, k + 1) {
		int min_c = 1e8;
		for (int ii = i - 6; ii >= 0; ii--) {
			min_c = min(min_c, c[ii]);
			dp[i][j] = min(dp[i][j], dp[ii][j - 1] + min_c);
		}
	} }

	// for (auto &row: dp) {
	// 	for (auto &cell: row) {
	// 		cout << cell << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	return dp[n][k];
}

void naive(cstr &s, cint &n, cvpii &v) {
	int docker_cnt = get_docker_cnt(s);
	int max_docker_cnt = s.size() / 6;
	auto [lesseq_v, greater_v] = get_lesseq_greater_v(v, max_docker_cnt, docker_cnt);

	if (lesseq_v == docker_cnt || (lesseq_v == -1 && greater_v == -1)) {
		cout << "0\n";
		return;
	}

	vi c(s.size(), 0); construct_c(c, s);

	int ans = s.size();
	if (lesseq_v != -1) {
		ans = docker_cnt - lesseq_v;
	}
	if (greater_v != -1) {
		int temp = naive_dp(c, greater_v);
		ans = min(ans, temp);
	}
	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase = 0; cin >> testcase;
	forn(i, testcase) {
		string s; cin >> s; int n; cin >> n;
		vpii v(n);
		forn(j, n) {
			cin >> v[j].first >> v[j].second;
		}
		solve(s, n, v);
		// naive(s, n, v);
	}
	return 0;
}
