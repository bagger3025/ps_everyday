#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Network {
	struct edge {
		int from;
		int to;
		int cap;
		int flow;

		inline bool full() const {
			return cap == flow;
		}

		inline int rest() const {
			return cap - flow;
		}

		inline void flip(int t) {
			flow += t;
		}
	};

	friend ostream &operator<<(ostream &os, const edge &e) {
		cout << "{" << e.from << " -> " << e.to << ", " << e.flow << "/" << e.cap << "}";
		return os;
	}

	int total_nodes;
	vector<edge> edges;
	vector<vector<int>> adj;
	int source, mid, sink;

	vector<int> lvl, ptr;

	void add_flow(int eidx, int flow) {
		edges[eidx].flip(flow);
		edges[eidx ^ 1].flip(-flow);
	}

	void add_edge(int from, int to, int cap) {
		edge e = {.from=from, .to=to, .cap=cap, .flow=0};
		int e_idx = edges.size(); edges.push_back(e);
		adj[from].push_back(e_idx);
	}

	void add_edges(int from, int to, int cap) {
		add_edge(from, to, cap);
		add_edge(to, from, 0);
	}

	int get_possible_flow(int node, int minflow = 1e9) {
		if (node == sink) return minflow;
		if (minflow == 0) return 0;

		for (int &i = ptr[node]; i < adj[node].size(); i++) {
			int eidx = adj[node][i];
			edge &e = edges[eidx];
			if (e.rest() == 0) continue;
			if (lvl[node] + 1 != lvl[e.to]) continue;

			int f = get_possible_flow(e.to, min(minflow, e.rest()));
			if (f == 0) continue;

			add_flow(eidx, f);
			return f;
		}
		return 0;
	}

	bool bfs() {
		fill(lvl.begin(), lvl.end(), -1);
		queue<int> q; q.push(source);
		lvl[source] = 0;
		while (!q.empty()) {
			int n = q.front(); q.pop();
			for (auto eidx: adj[n]) {
				if (edges[eidx].full()) continue;

				int y = edges[eidx].to;
				if (lvl[y] != -1) continue;

				lvl[y] = lvl[n] + 1;
				q.push(y);
				if (y == sink) return true;
			}
		}
		return false;
	}

public:
	Network(vector<vector<int>> &jobs, int n, int m, int k)
		: total_nodes(n + m + 3), adj(total_nodes),
			source(n + m), mid(n + m + 1), sink(n + m + 2),
			lvl(total_nodes), ptr(total_nodes) {

		for (int i = n; i < n + m; i++) {
			add_edges(i, sink, 1);
		}

		for (int i = 0; i < n; i++) {
			for (auto &job: jobs[i]) {
				job--;
				add_edges(i, n + job, 1);
			}
		}

		for (int i = 0; i < n; i++) {
			add_edges(source, i, 1);
			add_edges(mid, i, 1);
		}

		add_edges(source, mid, k);
	}

	int maxflow() {
		int i = 0;
		while (bfs()) {
			fill(ptr.begin(), ptr.end(), 0);
			int max_flow = get_possible_flow(source);
			while (max_flow) {
				i += max_flow;
				max_flow = get_possible_flow(source);
			}
		}
		return i;
	}

	void print() const {
		for (auto &row: adj) {
			for (auto &y: row) {
				cout << edges[y] << " ";
			} cout << endl;
		} cout << endl;
	}
};


void solve(vector<vector<int>> &jobs, int n, int m, int k) {
	Network net(jobs, n, m, k);

	int flow = net.maxflow();
	cout << flow;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m, k; cin >> n >> m >> k;
	vector<vector<int>> jobs;
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		vector<int> v(t);
		for (auto &e: v) cin >> e;
		jobs.push_back(v);
	}
	solve(jobs, n, m, k);
}
