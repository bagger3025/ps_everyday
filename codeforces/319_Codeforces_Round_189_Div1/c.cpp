#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

typedef long long ftype;
typedef complex<ftype> point;
typedef pair<long long, long long> pll;

#define x real
#define y imag

ftype dot(point a, point b) {
	cout << "dot(" << a << ", " << b << ") = ";
	ftype ret = (conj(a) * b).x();
	cout << ret << endl;
	return ret;
}

ftype cross(point a, point b) {
	cout << "cross(" << a << ", " << b << ") = ";
	ftype ret = (conj(a) * b).y();
	cout << ret << endl;
	return ret;
}

vector<point> hull, vecs;

void print_points(const vector<point> &v) {
	for (const point &c: v) {
		cout << c << " ";
	}
	cout << endl;
}

ostream &operator<<(ostream &os, const point &p) {
	os << "{ " << p.x() << ", " << p.y() << " }";
	return os;
}

void add_line(ftype k, ftype b) {
	cout << "add_line(" << k << ", " << b << "):" << endl;

	point nw = {k, b};
	while (!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
		cout << "dot returned < 0 => hull and vecs popped back: {" << hull.back() << ", " << vecs.back() << "}" << endl;
		hull.pop_back(); vecs.pop_back();
	}

	if (!hull.empty()) {
		vecs.push_back((point)1i * (nw - hull.back()));

		cout << "vecs pushed: " << vecs.back() << endl;
	}
	cout << "hull pushed: " << nw << endl;
	hull.push_back(nw);

	cout << endl;
}

long long get(ftype x) {
	cout << "get(" << x << ")" << endl;
	const point query = {x, 1};

	cout << "current vecs: "; print_points(vecs);
	cout << "current hull: "; print_points(hull);

	auto it = lower_bound(vecs.begin(), vecs.end(), query, [](const point &a, const point &b) {
		bool ret = cross(a, b) > 0;
		cout << "In lower_bound: ret = " << ret << endl;
		return ret;
	});

	if (vecs.end() == it) {
		cout << "Returend the last element" << endl;
	} else {
		cout << "Returned iterator pointing to = " << *it << endl;
	}
	
	auto ret = dot(query, hull[it - vecs.begin()]);
	cout << "Returning = " << ret << endl << endl;
	return ret;
}

void convex_hull_impl(const int &n, const vector<int> &as, const vector<int> &bs) {
	vector<long long> dp(n);
	dp[0] = 0;
	add_line(bs[0], dp[0]);

	for (int i = 1; i < n; i++) {
		long long next_dp = get(as[i]);
		dp[i] = next_dp;
		add_line(bs[i], dp[i]);
	}

	for (auto &d: dp) {
		cout << d << endl;
	} cout << endl;

	cout << dp[n - 1] << endl;
}

void naive_impl(const int &n, const vector<int> &as, const vector<int> &bs) {
	vector<long long> dp(n);
	dp[0] = 0;

	for (int i = 1; i < n; i++) {
		dp[i] = dp[0] + as[i] * bs[0];
		for (int j = 1; j < i; j++) {
			dp[i] = min(dp[i], dp[j] + as[i] * bs[j]);
		}
	}
	for (auto &d: dp) {
		cout << d << endl;
	} cout << endl;

	cout << dp[n - 1] << endl;
}

long long get_inter_point(const pll &f1, const pll &f2) {
	return (f2.second - f1.second) / (f1.first - f2.first) + 1;
}

class E {
	vector<pll> st;
	vector<long long> pt;
public:
	void add_slope(long long k, long long b) {
		while (st.size() >= 2) {
			pll l2 = st.back(); st.pop_back();
			pll l1 = st.back();

			long long p = get_inter_point(l1, {k, b});
			if (p > pt.back()) {
				st.push_back(l2);
				break;
			} else {
				pt.pop_back();
			}
		}

		int st_size = st.size();
		if (st_size == 0) {
			st.push_back({k, b});
		} else {
			auto back = st.back();

			// ax + b = kx + q
			// (a - k)x = q - b
			// x = (q - b) / (a - k) + 1
			st.push_back({k, b});
			pt.push_back(get_inter_point(back, {k, b}));
		}

		// cout << "After adding slope: " << endl;
		// cout << "st: ";
		// for (auto &s: st) {
		// 	cout << "{" << s.first << ", " << s.second << "} ";
		// } cout << endl;
		// cout << "pt: ";
		// for (auto &p: pt) {
		// 	cout << p << " ";
		// } cout << endl;
	}

	long long get_val(long long q) {
		auto it = upper_bound(pt.begin(), pt.end(), q);
		auto f = st[it - pt.begin()];
		return f.first * q + f.second;
	}
};

void convex_hull_data_structure(const int &n, const vector<int> &as, const vector<int> &bs) {
	vector<long long> dp(n);
	E e;

	dp[0] = 0;
	e.add_slope(bs[0], dp[0]);

	for (int i = 1; i < n; i++) {
		dp[i] = e.get_val(as[i]);
		e.add_slope(bs[i], dp[i]);
	}

	// for (auto &d: dp) {
	// 	cout << d << endl;
	// } cout << endl;

	cout << dp[n - 1] << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	vector<int> as(n), bs(n);
	for (int i = 0; i < n; i++) {
		cin >> as[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> bs[i];
	}
	// naive_impl(n, as, bs);
	// convex_hull_impl(n, as, bs);
	convex_hull_data_structure(n, as, bs);
}
