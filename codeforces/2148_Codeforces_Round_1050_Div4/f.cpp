#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;


int find_cand(vi &cands, const vvi &arr, int i) {
	vi tcands;

	for (++i; cands.size() > 1; i++) {
		int minval = 1'000'000;
		for (int &cand: cands) {
			if (arr[cand].size() == i) return cand;
			if (arr[cand][i] > minval) continue;
			if (arr[cand][i] < minval) {
				tcands.clear();
				minval = arr[cand][i];
			}
			tcands.push_back(cand);
		}
		cands.swap(tcands);
	}
	return cands[0];
}

void solve() {
	int n; cin >> n;
	vector<vector<int>> arr;
	int max_k = 0;
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		max_k = max(max_k, k);
		vector<int> subarr(k);
		for (int j = 0; j < k; j++) {
			cin >> subarr[j];
		}
		arr.push_back(subarr);
	}

	for (int i = 0; i < max_k;) {
		int minval = 1'000'000;
		vector<int> cands;
		for (int j = 0; j < arr.size(); j++) {
			if (arr[j].size() <= i) {
				while (!arr.empty() && arr.back().size() <= i) {
					arr.pop_back();
				}
				if (j >= arr.size()) break;
				arr[j] = arr.back(); arr.pop_back();
			}
			if (arr[j][i] > minval) continue;
			if (arr[j][i] < minval) {
				cands.clear();
				minval = arr[j][i];
			}
			cands.push_back(j);
		}

		int cand;
		if (cands.size() == 1) {
			cand = cands[0];
		} else {
			cand = find_cand(cands, arr, i);
		}

		for (; i < arr[cand].size(); i++) {
			cout << arr[cand][i] << " ";
		}
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	for (int tc = 0; tc < t; tc++) {
		solve();
	}
}
