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
		int cnt[4];
	};

	friend ostream &operator<<(ostream &os, const ele &e) {
		os << "{.l=" << e.l << ", .r=" << e.r << ", .lazy=" << e.lazy << ", .cnt={ "
			<< e.cnt[0] << ", " << e.cnt[1] << ", " << e.cnt[2] << ", " << e.cnt[3] << " } }";
		return os;
	}

	typedef vector<ele> vele;

	vele arr;
	int n;

	void resolve_ele(int idx) {
		ele &e = arr[idx];
		if (!e.lazy) return;

		e.lazy = 0;
		if (e.l != e.r) {
			ele &le = arr[left(idx)];
			le.lazy = !le.lazy;
			ele &re = arr[right(idx)];
			re.lazy = !re.lazy;
		}
		swap(e.cnt[0], e.cnt[2]);
		swap(e.cnt[1], e.cnt[3]);
	}

	void set_cnt(ele &e, ele &ch1, ele &ch2) {
		forn(i, 4) {
			e.cnt[i] = max(ch1.cnt[i] + ch2.cnt[i ^ (ch1.cnt[i] % 2)], ch2.cnt[i]);
		}
	}

	void set_cnt(int idx) {
		set_cnt(arr[idx], arr[left(idx)], arr[right(idx)]);
	}

	inline int left(int i) {
		return 2 * i + 1;
	}

	inline int right(int i) {
		return 2 * i + 2;
	}

	void rec_init(int idx, int l, int r, cvi &v) {
		if (l == r) {
			arr[idx] = {.l=l, .r=r, .lazy=0, .cnt={0}};
			arr[idx].cnt[v[l]] = 1;
			return;
		}
		int mid = (l + r) / 2;
		rec_init(left(idx), l, mid, v);
		rec_init(right(idx), mid + 1, r, v);

		arr[idx] = {.l=l, .r=r, .lazy=0, .cnt= { 0 }};
		set_cnt(idx);
	}

	void rec_flip(int idx, int l, int r) {
		ele &e = arr[idx];
		if (r < e.l || e.r < l) return;
		if (l <= e.l && e.r <= r) {
			// cout << "idx = " << idx << ", before flipping: " << e << endl;
			e.lazy = !e.lazy;

			// cout << "idx = " << idx << ", resolve result = " << e << endl;
			return;
		}
		// cout << "idx = " << idx << ", before resolving: " << e << endl;
		resolve_ele(idx);
		rec_flip(left(idx), l, r); resolve_ele(left(idx));
		rec_flip(right(idx), l, r); resolve_ele(right(idx));
		set_cnt(idx);
		// cout << "Process finished idx = " << idx << ", ele = " << e << endl;
	}

	ele rec_val(int idx, int l, int r) {
		// cout << "idx = " << idx << endl;
		ele &e = arr[idx];
		if (r < e.l || e.r < l) return {.l = 0, .r = 0, .lazy = 0, .cnt = { 0 }};

		resolve_ele(idx);
		if (l <= e.l && e.r <= r) {
			// cout << "idx = " << idx <<  ", returning " << e << endl;
			return e;
		}

		ele ret;
		ele lele = rec_val(left(idx), l, r);
		ele rele = rec_val(right(idx), l, r);
		set_cnt(ret, lele, rele);
		// cout << "idx = " << idx <<  ", returning " << ret << endl;
		return ret;
	}
public:
	LazySegTree(cvi &v): arr(4 * v.size()), n(v.size()) {
		rec_init(0, 0, n - 1, v);
	}

	void flip(int l, int r) {
		r--;
		// cout << "flip l = " << l << ", r = " << r << endl;
		rec_flip(0, l, r);
	}

	int get_val(int l, int r) {
		r--;
		return rec_val(0, l, r).cnt[2];
	}

	void print() const {
		for (auto &e: arr) {
			cout << e << " ";
		} cout << endl;
	}
};


struct stack_ele {
	int v;
	bool first;
};

vi make_eulien(cint &n, cvi &v, cvvi &adj, vi &enter, vi &node_exit) {
	vi ret; ret.reserve(n);
	vector<bool> visited(n, false);

	stack<stack_ele> s;
	s.push({0, true});
	while (!s.empty()) {
		auto t = s.top(); s.pop();
		if (t.first && visited[t.v]) continue;
		if (visited[t.v]) {
			node_exit[t.v] = ret.size();
			ret.push_back(v[t.v] == 1 ? 3 : 1);
			continue;
		}

		visited[t.v] = true;
		s.push({t.v, false});
		enter[t.v] = ret.size();
		ret.push_back(v[t.v] == 1 ? 2 : 0);

		for (auto &y: adj[t.v]) {
			if (visited[y]) continue;
			s.push({y, true});
		}
	}

	return ret;
}

void solve(int n, cvi &v, cvvi &adj, cvi &qry) {
	vi enter(n), node_exit(n);
	vi eulien = make_eulien(n, v, adj, enter, node_exit);
	// for (auto &e: eulien) {
	// 	cout << e << " ";
	// } cout << endl;

	LazySegTree st(eulien);

	// st.print();

	cout << st.get_val(0, 2 * n) / 2<< "\n";
	for (auto q: qry) {
		q--;
		st.flip(enter[q], node_exit[q] + 1);
		cout << st.get_val(0, 2 * n) / 2 << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(_t, t) {
		int n; cin >> n;
		vi v(n); for (int &e: v) cin >> e;
		vvi adj(n);
		forn (_n, n - 1) {
			int u, v; cin >> u >> v; u--; v--;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		int qn; cin >> qn;
		vi qry(qn); for (auto &q: qry) cin >> q;
		solve(n, v, adj, qry);
	}
}
