#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef const vi cvi;
typedef const vvi cvvi;

typedef vector<ll> vl;
typedef vector<vl> vvl;

typedef pair<ll, ll> pll;
typedef const pll cpll;

typedef pll vele;

typedef vector<vele> ve;

class E {
private:
	ve lines;
	vl pts;

	int track_idx = 0;

	ll cal(cpll &l, const ll &x) {
		return l.first * x + l.second;
	}

	// ax + b = cx + d
	// x = (d - b) / (a - c)
	long long get_inter_pt(cpll &l1, cpll &l2) {
		return (l2.second - l1.second) / (l1.first - l2.first) + 1;
	}
public:
	void add_line(const pll &line) {
		// cout << "add_line(" << line.first << ", " << line.second << ")" << endl;

		while (lines.size() >= 2) {
			auto l = lines.back();

			if (cal(l, pts.back()) < cal(line, pts.back())) {
				break;
			}
			lines.pop_back(); pts.pop_back(); continue;
		}
		track_idx = min((int)pts.size(), track_idx);

		if (lines.size() == 0) {
			lines.push_back(line);
		} else {
			pts.push_back(get_inter_pt(lines.back(), line));
			lines.push_back(line);
		}

		// cout << "Now, lines = ";
		// for (const auto &l: lines) {
		// 	cout << "(" << l.first << ", " << l.second << ") ";
		// } cout << endl;
		// cout << "pts = ";
		// for (const auto &p: pts) {
		// 	cout << p << " ";
		// } cout << endl;
		// cout << track_idx << endl;
		// cout << endl;
	}

	ll query(ll x) {
		// cout << "For query x = " << x << ", " << endl;
		while (track_idx < pts.size() && pts[track_idx] <= x) {
			track_idx++;
		}
		cpll &line = lines[track_idx];
		ll ret = line.first * x + line.second;
		// cout << "track_idx = " << track_idx << ", Returning ret = " << ret << endl << endl;
		return ret;
	}
	
};

vl get_asum(cvi &v) {
	const int n = v.size();

	vl asum(n + 1);
	asum[0] = 0;

	for (int i = 0; i < n; i++) {
		asum[i + 1] = asum[i] + v[i];
	}
	return asum;
}

void convex_hull(ll n, ll a, ll b, ll c, const vi &v) {
	vl dp(n + 1);
	vl asum = get_asum(v);
	E e;

	dp[0] = 0;
	e.add_line({0, 0});

	for (int i = 1; i <= n; i++) {
		dp[i] = -e.query(asum[i]) + a * asum[i] * asum[i] + b * asum[i] + c;
		e.add_line({2 * a * asum[i], -a * asum[i] * asum[i] + b * asum[i] - dp[i]});
	}

	// for (auto &d: dp) {
	// 	cout << d << endl;
	// } cout << endl;

	cout << dp[n] << endl;
}

void naive(ll n, ll a, ll b, ll c, const vi &v) {
	vl dp(n + 1);
	vl asum = get_asum(v);
	dp[0] = 0;

	for (int i = 1; i <= n; i++) {
		// cout << "i = " << i << endl;
		ll maxval = a * asum[i] * asum[i] + b * asum[i] + c;
		// cout << a << " * " << asum[i] << "^2 + " << b << " * " << asum[i] << " + " << c << " = " << maxval << endl;
		for (int j = 1; j < i; j++) {
			ll temp_asum = asum[i] - asum[j];
			ll temp = dp[j] + a * temp_asum * temp_asum + b * temp_asum + c;
			// cout << dp[j] << " + " << a << " * " << temp_asum << "^2 + " << b << " * " << temp_asum << " + " << c << " = " << temp << endl;
			maxval = max(maxval, temp);
		}
		dp[i] = maxval;
		// cout << endl;
	}

	// for (auto &d: dp) {
	// 	cout << d << endl;
	// } cout << endl;

	cout << dp[n] << endl;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ll n; cin >> n;
	ll a, b, c; cin >> a >> b >> c;
	vi v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	convex_hull(n, a, b, c, v);
	// naive(n, a, b, c, v);
	
	return 0;
}
