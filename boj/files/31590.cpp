#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

using namespace std;

class SplayTree {
	struct Node {
		int size;
		char ch;
		Node *left, *right, *par;

		void resize() {
			int lsize = size_node(left);
			int rsize = size_node(right);
			size = lsize + rsize + 1;
		}

		void rotate_right() {
			// assume left exists
			Node *node = left;

			left = node->right; if (left) left->par = this;
			node->par = par; if (par) { if (par->right == this) par->right = node; else par->left = node; }
			node->right = this; par = node;

			resize();
			node->resize();
		}

		void rotate_left() {
			// assume right exists
			Node *node = right;

			right = node->left; if (right) right->par = this;
			node->par = par; if (par) { if (par->right == this) par->right = node; else par->left = node; }
			node->left = this; par = node;

			resize();
			node->resize();
		}

		~Node() {
			delete left;
			delete right;
		}
	};

	static int size_node(Node *node) {
		if (node == nullptr) return 0;
		return node->size;
	}

	Node *head = nullptr;

	void rotate_right(Node *node) {
		node->rotate_right();
	}

	void rotate_left(Node *node) {
		node->rotate_left();
	}

	void rotate(Node *node) {
		Node *par = node->par;
		if (par->left == node) {
			rotate_right(par);
		} else {
			rotate_left(par);
		}
	}

	void splay(Node *node) {
		// cout << "node ch = " << node->ch << endl;
		// inorder(node); cout << endl;
		while (node->par != nullptr) {
			Node *par = node->par;
			Node *grandpar = par->par; if (grandpar == nullptr) { rotate(node); break; }

			if ((grandpar->left == par) == (par->left == node)) {
				// LL or RR
				rotate(par);
				rotate(node);
			} else {
				// LR or RL
				rotate(node);
				rotate(node);
			}

			// inorder(node); cout << endl;
		}
		head = node;
		// cout << "Splay end" << endl;
	}

	string inorder(Node *node) const {
		string ret;
		if (node == nullptr) return ret;
		stack<Node *> st;
		while (node) {
			st.push(node);
			node = node->left;
		}
		while (!st.empty()) {
			node = st.top(); st.pop();
			ret += node->ch;
			node = node->right;
			while (node) {
				st.push(node);
				node = node->left;
			}
		}
		return ret;
		// inorder(node->left, s);
		// s += node->ch;
		// inorder(node->right, s);
	}

	void find_and_splay(int idx) {
		Node *node = head;

		while (true) {
			int lsize = size_node(node->left);
			if (lsize == idx) break;
			if (lsize < idx) {
				node = node->right;
				idx -= lsize + 1;
			} else {
				node = node->left;
			}
		}
		splay(node);
	}
public:
	SplayTree(const string &s) {
		head = new Node{.size=(int)s.size(), .ch=s[0], .left=nullptr, .right=nullptr, .par=nullptr};
		Node *node = head;

		for (int i = 1; i < s.size(); i++) {
			node->right = new Node{.size=(int)s.size() - i, .ch=s[i], .left=nullptr, .right=nullptr, .par=node};
			node = node->right;
		}
	}

	~SplayTree() {
		delete head;
	}

	void insert(char c, int idx) {
		if (head == nullptr) {
			head = new Node{.size=1, .ch=c, .left=nullptr, .right=nullptr, .par=nullptr};
			return;
		}

		if (idx == 0) {
			find_and_splay(0);
			head->left = new Node{.size=1, .ch=c, .left=nullptr, .right=nullptr, .par=head};
			splay(head->left);
			return;
		}

		find_and_splay(idx - 1);

		Node *left = head, *right = head->right;
		head->right = nullptr; head->resize(); if (right) right->par = nullptr;
		head = new Node{.size=1, .ch=c, .left=left, .right=right, .par=nullptr};

		if (head->left) head->left->par = head;
		if (head->right) head->right->par = head;

		head->resize();
	}

	string remove(int l, int r) {
		Node *lhead = nullptr, *rhead = nullptr;
		if (r < head->size - 1) {
			find_and_splay(r + 1); 
			rhead = head; head = head->left;
			rhead->left = nullptr; head->par = nullptr;
			rhead->resize();
		}
		if (l > 0) {
			find_and_splay(l - 1);
			lhead = head; head = head->right;
			lhead->right = nullptr; head->par = nullptr;
			lhead->resize();
		}

		string ret = inorder(head);
		delete head;

		if (lhead == nullptr) {
			head = rhead;
		} else if (rhead == nullptr) {
			head = lhead;
		} else {
			head = lhead;
			head->right = rhead; rhead->par = head;
			head->resize();
		}
		return ret;
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, q; cin >> n >> q;
	string s; cin >> s;
	SplayTree st(s);
	for (int _q = 0; _q < q; _q++) {
		int x; cin >> x;
		if (x == 1) {
			char c; int i; cin >> c >> i; i--;
			st.insert(c, i);
		} else {
			int l, r; cin >> l >> r; l--; r--;
			string ret = st.remove(l, r);
			cout << ret << "\n";
		}
	}
}
