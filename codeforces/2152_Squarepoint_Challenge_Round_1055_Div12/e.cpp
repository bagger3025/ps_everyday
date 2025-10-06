#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define all(x) x.begin(), x.end()

typedef vector<int> vi;
typedef const vi cvi;

typedef pair<int, int> pii; typedef vector<pii> vpii;
typedef const pii cpii; typedef const vpii cvpii;

vector<int> make_query(vector<int> &query) {
	cout << "? " << query.size();

	for (auto &q: query) {
		cout << " " << q;
	} cout << endl; cout.flush();

	int num;
	cin >> num;
	vector<int> ret(num);
	for (auto &e: ret) cin >> e;

	return ret;
}

void print_answer(vector<int> &answer) {
	cout << "!";
	for (auto &a: answer) cout << " " << a;
	cout << endl; cout.flush();
}

void solve(int n) {
	vector<int> query(n * n + 1);
	forn(i, n * n + 1) {
		query[i] = i + 1;
	}
	vector<vector<int>> ans_list;

	forn(_x, n) {
		vector<int> ans = make_query(query);
		ans_list.push_back(ans);

		if (ans.size() >= n + 1) {
			ans.resize(n + 1); print_answer(ans); return;
		}

		int lp = 0, rp = 0, ap = 0;
		while (rp < query.size() && ap < ans.size()) {
			if (query[rp] == ans[ap]) {
				lp--; ap++;
			} else if (lp != rp) {
				query[lp] = query[rp];
			}
			lp++; rp++;
		}
		while (rp < query.size()) {
			query[lp] = query[rp];
			lp++; rp++;
		}
		query.resize(lp);
	}

	vector<int> ans;
	int val = query[0]; ans.push_back(val);
	for (int i = ans_list.size() - 1; i >= 0; i--) {
		auto it = upper_bound(all(ans_list[i]), val);
		--it;
		val = *it; ans.push_back(val);
	}
	reverse(all(ans));
	print_answer(ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	forn(tc, t) {
		int n; cin >> n;
		solve(n);
	}
}
