#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;


class SegTree {
	struct ele {
		int l, r;
		long long left_best;
		long long right_best;
		long long seg_best;
		long long total;

		ele operator+(const ele &other) const {
			return ele {
				.l=this->l,
				.r=other.r,
				.left_best=max(this->left_best, this->total + other.left_best),
				.right_best=max(other.right_best, other.total + this->right_best),
				.seg_best=max({this->seg_best, other.seg_best, this->right_best + other.left_best}),
				.total=this->total + other.total
			};
		}
	};

	friend ostream &operator<<(ostream &os, const ele &e) {
		cout << "{" << e.l << "-" << e.r << ": seg=" << e.seg_best << ", left=" << e.left_best << ", right=" << e.right_best << ", total= " << e.total << "}";
		return os;
	}

	vector<ele> arr;

	inline int left(int idx) const {
		return idx * 2 + 1;
	}

	inline int right(int idx) const {
		return idx * 2 + 2;
	}

	void init(int idx, int l, int r, const vector<int> &v) {
		if (l == r) {
			arr[idx] = {.l=l, .r=r, .left_best=v[l], .right_best=v[l], .seg_best=v[l], .total=v[l]};
			return;
		}

		int mid = (l + r) / 2;
		init(left(idx), l, mid, v);
		init(right(idx), mid + 1, r, v);

		const ele &le = arr[left(idx)];
		const ele &re = arr[right(idx)];

		arr[idx] = le + re;
	}

	ele recsum(int idx, int l, int r) {
		if (l <= arr[idx].l && arr[idx].r <= r) return arr[idx];
		const ele &le = arr[left(idx)];
		const ele &re = arr[right(idx)];

		if (r < re.l) return recsum(left(idx), l, r); 
		if (le.r < l) return recsum(right(idx), l, r);

		ele lsum = recsum(left(idx), l, r);
		ele rsum = recsum(right(idx), l, r);
		return lsum + rsum;
	}

	void print_indent(int indent = 0) const {
		for (int i = 0; i < indent; i++) {
			cout << "\t";
		}
	}
public:
	SegTree(const vector<int> &v): arr(v.size() * 4) {
		init(0, 0, v.size() - 1, v);
	}

	void print(int indent = 0, int idx = 0) const {
		print_indent(indent);

		cout << "idx = " << idx << ", e = " << arr[idx] << endl;
		if (arr[idx].l != arr[idx].r) {
			print(indent + 1, left(idx));
			print(indent + 1, right(idx));
			
		}
	}

	long long get_maxsum(int l, int r) {
		r--;
		ele e = recsum(0, l, r);
		return e.seg_best;
	}
	
};

void solve(const vector<int> &v, const vector<pair<int, int>> &qry) {
	SegTree st(v);
	// st.print();

	for (auto &q: qry) {
		long long res = st.get_maxsum(q.first, q.second + 1);
		cout << res << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	vector<int> v(n); for (auto &e: v) cin >> e;
	int m; cin >> m;
	vector<pair<int, int>> qry(m); for (auto &qele: qry) { cin >> qele.first >> qele.second; qele.first--, qele.second--; }
	solve(v, qry);
}
