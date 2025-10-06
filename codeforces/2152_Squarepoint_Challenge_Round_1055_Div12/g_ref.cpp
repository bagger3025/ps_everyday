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

class Tree {
	struct node {
		int idx;
		int monster;
		
		vector<node *> children;

		void flip() {
			monster = !monster;
			for (auto c: children) {
				c->flip();
			}
		}
	};

	typedef vector<node> vnode;
	vnode arr;

	void rec_init(int idx, cvvi &adj, vector<bool> &visited) {
		if (visited[idx]) return;
		visited[idx] = true;

		node &n = arr[idx];
		for (auto &child: adj[idx]) {
			if (visited[child]) continue;

			rec_init(child, adj, visited);
			n.children.push_back(&arr[child]);
		}
	}

	int get_path(const node &n) const  {
		int path = 0;
		for (auto child: n.children) {
			path += get_path(*child);
		}
		if (path == 0 && n.monster) return 1;
		return path;
	}
public:
	Tree(cvvi &adj, cvi &v): arr(adj.size()) {
		forn(i, v.size()) {
			arr[i].idx = i;
			arr[i].monster = v[i];
		}
		vector<bool> visited(v.size(), false);
		rec_init(0, adj, visited);
	}

	int get_path() const {
		return get_path(arr[0]);
	}

	void flip(int node_idx) {
		node &n = arr[node_idx];
		n.flip();
	}
	
};

void solve(int n, cvi &v, cvvi &adj, cvi &qry) {
	Tree t(adj, v);
	cout << t.get_path() << "\n";
	for (auto &q: qry) {
		t.flip(q - 1);
		cout << t.get_path() << "\n";
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
