#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

class SegmentTree {
	struct ele {
		int l, r;
		int sum;
	};

	friend ostream &operator<<(ostream &os, const ele &e) {
		cout << "{" << e.l << "~" << e.r << ", " << e.sum << "}";
		return os;
	}

	vector<ele> arr;

	inline int left(int idx) {
		return 2 * idx + 1;
	}

	inline int right(int idx) {
		return 2 * idx + 2;
	}

	void init(int idx, int l, int r, const vector<int> &v) {
		if (l == r) {
			arr[idx] = {.l=l, .r=r, .sum=v[l]};
			return;
		}

		int mid = (l + r) / 2;
		init(left(idx), l, mid, v);
		init(right(idx), mid + 1, r, v);
		arr[idx] = {.l=l, .r=r, .sum=arr[left(idx)].sum + arr[right(idx)].sum};
	}

	void recadd(int idx, int x) {
		if (arr[idx].r < x || x < arr[idx].l) {
			return;
		}
		if (arr[idx].l == x && arr[idx].r == x) {
			arr[idx].sum++; return;
		}

		recadd(left(idx), x);
		recadd(right(idx), x);
		arr[idx].sum = arr[left(idx)].sum + arr[right(idx)].sum;
	}

	int rec_sum(int idx, int l, int r) {
		if (arr[idx].r < l || r < arr[idx].l) return 0;
		if (l <= arr[idx].l && arr[idx].r <= r) return arr[idx].sum;

		int lsum = rec_sum(left(idx), l, r);
		int rsum = rec_sum(right(idx), l, r);
		return lsum + rsum;
	}

public:
	SegmentTree(const vector<int> &v): arr(v.size() * 4) {
		init(0, 0, v.size() - 1, v);
	}

	void print() const {
		for (auto &e: arr) cout << e << " ";
		cout << endl;
	}

	void add(int v) {
		recadd(0, v);
	}

	int range_sum(int l, int r) {
		r--;
		return rec_sum(0, l, r);
	}
};

void get_euclidean(const vector<vector<int>> &adj, vector<pair<int, int>> &ranges, vector<int> &level, int c) {
	vector<int> ret;

	stack<int> s; s.push(c);
	int time = 0;
	level[c] = 1;
	while (!s.empty()) {
		int t = s.top();
		if (ranges[t].first != -1) {
			s.pop();
			ranges[t].second = time;
			continue;
		}

		ranges[t].first = time++;
		for (auto y: adj[t]) {
			if (level[y] != -1) continue;
			s.push(y);
			level[y] = level[t] + 1;
		}
	}
}

void solve(vector<vector<int>> &adj, int c, vector<pair<int, int>> &qry) {
	const int n = adj.size();
	vector<pair<int, int>> ranges(n, {-1, -1});
	vector<int> level(n, -1);

	get_euclidean(adj, ranges, level, c);

	// for (auto &r: ranges) {
	// 	cout << "{" << r.first << ", " << r.second << "} ";
	// } cout << endl;

	// for (auto &l: level) {
	// 	cout << l << " ";
	// } cout << endl;

	SegmentTree st(vector<int>(n, 0));

	for (auto &q: qry) {
		if (q.first == 1) {
			st.add(ranges[q.second].first);
		} else {
			cout << (long long)st.range_sum(ranges[q.second].first, ranges[q.second].second) * level[q.second] << "\n";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, c; cin >> n >> c; c--;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int x, y; cin >> x >> y; x--; y--;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	int q; cin >> q;
	vector<pair<int, int>> qry(q);
	for (auto &qele: qry) {
		cin >> qele.first >> qele.second; qele.second--;
	}
	solve(adj, c, qry);
}
