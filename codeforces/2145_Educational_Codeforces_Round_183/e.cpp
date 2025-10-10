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

class LazySegTree {
	struct ele {
		int l, r;
		int lazy;
		int val;
	};

	friend ostream &operator<<(ostream &os, const ele &e) {
		os << "{" << e.l << "-" << e.r << ": " << e.lazy << ", " << e.val << "}";
		return os;
	}

	vector<ele> arr;

	inline int left(int idx) {
		return idx * 2 + 1;
	}

	inline int right(int idx) {
		return idx * 2 + 2;
	}

	void resolve(int idx) {
		ele &e = arr[idx];
		if (e.l != e.r) {
			arr[left(idx)].lazy += e.lazy;
			arr[right(idx)].lazy += e.lazy;
		}
		e.val += e.lazy; e.lazy = 0;
	}

	void init(int idx, int l, int r) {
		if (l == r) {
			arr[idx] = {.l=l, .r=r, .lazy=0, .val=-l};
			return;
		}

		int mid = (l + r) / 2;
		init(left(idx), l, mid);
		init(right(idx), mid + 1, r);

		arr[idx] = {.l=l, .r=r, .lazy=0, .val=min(arr[left(idx)].val, arr[right(idx)].val)};
	}

	void rec_addval(int idx, int from, int val) {
		ele &e = arr[idx];
		if (e.r < from) return;
		if (from <= e.l) {
			e.lazy += val;
			return;
		}

		resolve(idx);
		rec_addval(left(idx), from, val); resolve(left(idx));
		rec_addval(right(idx), from, val); resolve(right(idx));
		e.val = min(arr[left(idx)].val, arr[right(idx)].val);
	}

	int rec_getidx(int idx) {
		resolve(idx);
		if (arr[idx].val >= 0) return arr[idx].r;
		if (arr[idx].l == arr[idx].r) return -1;

		int ret = rec_getidx(left(idx));
		if (ret == -1) return -1;
		if (ret != arr[left(idx)].r) return ret;

		int ridx = rec_getidx(right(idx));
		if (ridx == -1) return ret;
		else return ridx;
	}
public:
	LazySegTree(int n): arr(4 * n) {
		init(0, 0, n - 1);
	}

	void addval(int from, int val) {
		if (from > arr[0].r) return;
		rec_addval(0, from, val);
	}

	int get_idx() {
		return rec_getidx(0);
	}

	void print() {
		for (int i = 0; i < arr.size(); i++) {
			cout << i << ": " << arr[i] << "\n";
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int ac, dr; cin >> ac >> dr;
	int n; cin >> n;
	vi scores(n);
	for (auto &a: scores) cin >> a;

	LazySegTree st(n + 1);
	// st.print();
	forn(i, n) {
		int t; cin >> t;
		scores[i] = max(scores[i] - ac, 0) + max(t - dr, 0); 
		st.addval(scores[i] + 1, 1);
	}
	// st.print();
	int m; cin >> m;
	forn(_m, m) {
		int k, kac, kdr; cin >> k >> kac >> kdr; k--;
		int score = max(kac - ac, 0) + max(kdr - dr, 0);
		st.addval(scores[k] + 1, -1);
		st.addval(score + 1, 1);
		// st.print();
		scores[k] = score;
		cout << st.get_idx() << "\n";
	}
}
