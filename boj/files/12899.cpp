#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

using namespace std;

class SegTree {
	struct ele {
		int val;
	};

	vector<ele> arr;

	inline int left(int idx) {
		return idx * 2 + 1;
	}

	inline int right(int idx) {
		return idx * 2 + 2;
	}

	int recinsert(int idx, int l, int r, const int &val) {
		if (l == val && r == val) {
			arr[idx].val += 1;
			return arr[idx].val;
		}
		if (r < val || val < l) return arr[idx].val;

		int mid = (l + r) / 2;
		int lval = recinsert(left(idx), l, mid, val);
		int rval = recinsert(right(idx), mid + 1, r, val);

		return arr[idx].val = lval + rval;
	}

	int recdelete(int idx, int l, int r, int k) {
		if (arr[idx].val < k) return -1;
		if (l == r) {
			arr[idx].val -= 1;
			return l;
		}

		int retval;
		int mid = (l + r) / 2;
		if (k <= arr[left(idx)].val) {
			retval = recdelete(left(idx), l, mid, k);
		} else {
			retval = recdelete(right(idx), mid + 1, r, k - arr[left(idx)].val);
		}

		arr[idx].val = arr[left(idx)].val + arr[right(idx)].val;
		return retval;
	}
	int n;
public:
	SegTree(int n): arr(4 * n, {0}), n(n) {
	}

	void insert(int val) {
		recinsert(0, 1, n, val);
	}

	int del(int k) {
		return recdelete(0, 1, n, k);
	}
};


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	SegTree st(2'000'000);
	for (int i = 0; i < n; i++) {
		int t, x; cin >> t >> x;
		if (t == 1) {
			st.insert(x);
		} else {
			cout << st.del(x) << "\n";
		}
	}
}
