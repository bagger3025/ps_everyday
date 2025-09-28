#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 998244353;

typedef long long ll; typedef vector<ll> vl; typedef vector<vl> vvl;
typedef const ll cll; typedef const vl cvl; typedef const vvl cvvl;

typedef vector<int> vi; typedef vector<vi> vvi; typedef vector<vvi> vvvi;
typedef const int cint; typedef const vi cvi; typedef const vvi cvvi; typedef const vvvi cvvvi;

typedef vector<string> vs;
typedef const vs cvs;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

typedef pair<ll, ll> pll; typedef vector<pll> vpll;
typedef const pll cpll; typedef const vpll cvpll;

typedef const string cstr;

#define forn(i, n) for (int i = 0; i < int(n); i++)

// mod = q * a + p
// a^-1 * mod = q + p * a^-1
// a^-1 = -q * p^-1
int rev_mod(int r, cint &mod = MOD) {
	return r == 1 ? 1 : MOD - (mod / r) * rev_mod(mod % r);
}

ll pow_mod(int a, int p, cint &mod = MOD) {
	if (p == 0) return 1;
	if (p == 1) return a;
	ll ret = pow_mod(a, p / 2, mod);
	ret = (ret * ret) % mod;
	if (p % 2 == 1) {
		return (ret * a) % mod;
	} else {
		return ret;
	}
}

class TrieNode {
public:
	TrieNode(int idx, bool is_end = false): idx(idx), is_end(is_end) {}

	int child_idx;
	int idx;
	bool is_end;
	TrieNode *children[2] = { 0 };
	TrieNode *next_node[2] = { 0 };
	TrieNode *go = NULL;

	void print(int indent = 0, int child_num = -1) {
		print_indent(indent);
		if (child_num >= 0) {
			cout << "child = " << child_num << ", ";
		}
		cout << "idx = " << idx << ", is_end = " << (is_end ? "true": "false");
		if (go) {
			cout << ", go = " << go->idx;
		}
		cout << endl;
		for (int i = 0; i < 2; i++) {
			if (!children[i]) continue;
			children[i]->print(indent + 2, i);
		}
	}

	void print_indent(int indent) {
		for (int i = 0; i < indent; i++) {
			cout << " ";
		}
	}

	TrieNode *next(int idx) {
		return next_node[idx];
	}
};

class Trie {
	TrieNode *head;
	vector<TrieNode *> nodes;

	int to_idx(char c) const {
		switch (c) {
			case '(': return 0;
			case ')': return 1;
			default: exit(1);
		}
	}

public:
	Trie(cvs &v) {
		head = make_new_node();
		head->next_node[0] = head;
		head->next_node[1] = head;
		
		for (const string &s: v) {
			TrieNode *cur_node = head;
			for (int i = 0; i < s.size(); i++) {
				cur_node = children_or_new(cur_node, to_idx(s[i]));
			}
			cur_node->is_end = true;
		}


		queue<pair<TrieNode *, TrieNode *>> q; q.push({head, head});
		while (!q.empty()) {
			auto node = q.front(); q.pop();
			TrieNode *par = node.first, *child = node.second;

			child->go = get_gonode(par, child->child_idx);

			if (child->go->is_end) {
				child->is_end = true;
			}

			for (int i = 0; i < 2; i++) {
				if (child->children[i]) {
					child->next_node[i] = child->children[i];
					q.push({child, child->children[i]});
				} else {
					child->next_node[i] = child->go->next_node[i];
				}
			}
		}
		// head->print();
	}

	TrieNode *get_gonode(TrieNode *parnode, int idx) {
		if (parnode == head) {
			return head;
		}
		parnode = parnode->go;
		if (parnode->children[idx]) return parnode->children[idx];
		else return get_gonode(parnode, idx);
	}

	TrieNode *children_or_new(TrieNode *par, int idx) {
		if (!par->children[idx]) {
			par->children[idx] = make_new_node();
			par->children[idx]->child_idx = idx;
		}
		return par->children[idx];
	}

	TrieNode *make_new_node(bool is_end = false) {
		TrieNode *tmp = new TrieNode(nodes.size(), is_end);
		nodes.push_back(tmp);
		return tmp;
	}

	TrieNode *operator[](int idx) {
		return nodes[idx];
	}

	int size() const { return nodes.size(); }

};

struct stack_ele {
	int k;
	int bal;
	int node;
};

struct vector_ele {
	bool visited;
	int k;
	int bal;
	int node;
};

ostream &operator<<(ostream &os, const vector_ele &ve) {
	os << "{" << (ve.visited ? "T" : "F") << ", " << ve.k << ", " << ve.bal << ", " << ve.node << "}";
	return os;
}

typedef vector<vector_ele> ve; typedef vector<ve> vve; typedef vector<vve> vvve;

void solve(cvs &v, cint &k) {
	cint n = v.size();

	Trie t(v);
	vvve dp(k + 1, vve(k / 2 + 1, ve(t.size(), {false})));

	queue<stack_ele> s;
	s.push({0, 0, 0});

	int ans = -1;
	while (!s.empty()) {
		stack_ele se = s.front(); s.pop();
		// cout << "se = " << se.k << ", " << se.bal << ", " << se.node << endl;

		if (se.k == k && se.bal == 0) {
			ans = se.node; break;
		}
		if (se.k + se.bal + 2 <= k) {
			auto next_node = t[se.node]->next(0);
			if (next_node && !next_node->is_end) {
				auto &next_dpnode = dp[se.k + 1][se.bal + 1][next_node->idx];
				if (!next_dpnode.visited) {
					s.push({se.k + 1, se.bal + 1, next_node->idx});
					next_dpnode = {true, se.k, se.bal, se.node};
				}
			}
		}

		if (se.bal > 0) {
			auto next_node = t[se.node]->next(1);
			if (next_node && !next_node->is_end) {
				auto &next_dpnode = dp[se.k + 1][se.bal - 1][next_node->idx];
				if (!next_dpnode.visited) {
					s.push({se.k + 1, se.bal - 1, next_node->idx});
					next_dpnode = {true, se.k, se.bal, se.node};
				}
			}
		}
	}
	// cout << "ans = " << ans << endl;

	// for (auto &row : dp) {
	// 	for (auto &row2: row) {
	// 		for (auto &cell: row2) {
	// 			cout << cell << " ";
	// 		} cout << endl;
	// 	} cout << endl;
	// } cout << endl;

	if (ans == -1) {
		vi open_side, close_side; // (()), ()()
		for (int i = 0; i < n; i++) {
			if (v[i] == "()") {
				cout << "-1"; return;
			}
			bool flag = false;
			bool to_open = false;
			for (int j = 0; !to_open && j < v[i].size(); j++) {
				if (!flag && v[i][j] == ')') flag = true;
				else if (flag && v[i][j] == '(') to_open = true;
			}
			if (to_open) {
				open_side.push_back(i + 1);
			} else {
				close_side.push_back(i + 1);
			}
		}

		cout << "2\n";
		for (int i = 0; i < k / 2; i++) {
			cout << '(';
		}
		for (int i = 0; i < k / 2; i++) {
			cout << ')';
		}
		cout << "\n";
		cout << open_side.size() << "\n";
		for (int &o: open_side) {
			cout << o << " ";
		}
		cout << "\n";
		for (int i = 0; i < k / 2; i++) {
			cout << "()";
		}
		cout << "\n";
		cout << close_side.size() << "\n";
		for (int &o: close_side) {
			cout << o << " ";
		}
	} else {
		vector_ele cur_node = {.visited = true, .k = k, .bal = 0, .node = ans};
		string ans = "";
		for (int i = k; i > 0; i--) {
			vector_ele next_node = dp[cur_node.k][cur_node.bal][cur_node.node];
			// cout << "next_node = " << next_node << endl;

			if (cur_node.bal + 1 == next_node.bal) {
				ans += ")";
			} else {
				ans += "(";
			}

			cur_node = next_node;
		}
		reverse(ans.begin(), ans.end());
		cout << 1 << "\n";
		cout << ans << "\n";
		cout << n << "\n";
		for (int i = 1; i <= n; i++) {
			cout << i << " ";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, k; cin >> n >> k;
	vs v(n);
	forn(j, n) {
		cin >> v[j];
	}
	solve(v, k);
	return 0;
}

const string al = "()";

struct aho_corasick {
    static const int AL = 2;
 
    struct node {
        int nxt[AL], go[AL];
        int p, pch; // p = parent idx, pch = child idx of parent
        int suf, ssuf;
        bool term;
        
        node() {
            memset(nxt, -1, sizeof(nxt));
            memset(go, -1, sizeof(go));
            suf = ssuf = -1;
            term = false;
        }
    };
 
    vector<node> nodes;
    vector<vector<int>> g;
    
    aho_corasick() {
        nodes.push_back(node());
    }
 
    void add(const string& s) {
        int v = 0;
        forn(i, s.size()) {
            int c = al.find(s[i]);
            if (nodes[v].nxt[c] == -1) {
                nodes.push_back(node());
                nodes[v].nxt[c] = nodes.size() - 1;
                nodes.back().p = v;		// parent idx
                nodes.back().pch = c;	// child idx of parent
            }
            v = nodes[v].nxt[c];
        }
        nodes[v].term = true;
    }
    
    int go(int v, int c) {
        if (nodes[v].go[c] != -1)
            return nodes[v].go[c];
        if (nodes[v].nxt[c] != -1)
            return nodes[v].go[c] = nodes[v].nxt[c];
        if (v == 0)
            return nodes[v].go[c] = 0;
        return nodes[v].go[c] = go(suf(v), c);
    }
    
    int suf(int v) {
        if (nodes[v].suf != -1)
            return nodes[v].suf;
        if (v == 0 || nodes[v].p == 0)
            return nodes[v].suf = 0;
        return nodes[v].suf = go(suf(nodes[v].p), nodes[v].pch);
    }
    
    int ssuf(int v) {
        if (nodes[v].ssuf != -1)
            return nodes[v].ssuf;
        if (v == 0 || nodes[v].p == 0)
            return nodes[v].ssuf = 0;
        int s = suf(v);
        if (nodes[s].term)
            return nodes[v].ssuf = s;
        return nodes[v].ssuf = ssuf(s);
    }
    
    void build_tree() {
        g.resize(nodes.size());
        forn(v, nodes.size()) {
            int u = suf(v);
            if (v != u)
                g[u].push_back(v);
        }
    }
};
