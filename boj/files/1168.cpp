#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

class SegTree {
	struct ele {
		int l;
		int r;
		int val;
	};

	vector<ele> arr;

	inline int left(int idx) {
		return 2 * idx + 1;
	}

	inline int right(int idx) {
		return 2 * idx + 2;
	}

	void init(int idx, int l, int r) {
		if (l == r) {
			arr[idx] = {l, r, 1};
			return;
		}

		int mid = (l + r) / 2;
		init(left(idx), l, mid);
		init(right(idx), mid + 1, r);
		arr[idx] = {l, r, r - l + 1};
	}

	int recith(int idx, int n) {
		if (arr[idx].l == arr[idx].r) {
			arr[idx].val = 0;
			return arr[idx].l;
		}

		ele &lele = arr[left(idx)];
		arr[idx].val--;
		if (n <= lele.val) {
			return recith(left(idx), n);
		} else {
			return recith(right(idx), n - lele.val);
		}
	}
public:
	SegTree(int n): arr(4 * n) {
		init(0, 1, n);
	}
	
	int ith(int n) {
		return recith(0, n);
	}
};

void solve(const int &n, const int &k) {
	cout << "<";
	SegTree st(n);

	int val = k;
	for (int i = 0; i < n; i++) {
		// cout << endl << "val = " << val << endl;
		int ret = st.ith(val);
		
		cout << ret;
		if (i != n - 1) {
			cout << ", ";
		}
		val += k - 1;
		if (n - i - 1 > 0) {
			val = ((val + n - i - 2) % (n - i - 1)) + 1;
		}
	}
	cout << ">";
	
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, k; cin >> n >> k;
	solve(n, k);
}
