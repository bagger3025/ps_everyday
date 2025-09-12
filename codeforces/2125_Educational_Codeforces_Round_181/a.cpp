#include <iostream>
#include <algorithm>

using namespace std;

void solve(string &s) {
	const int n = s.size();
	int lp = 0;
	while (lp < n && s[lp] == 'T') lp++;

	for (int rp = lp + 1; rp < n; rp++) {
		if (s[rp] != 'T') continue;
		swap(s[lp], s[rp]);
		lp++;
	}
	
	cout << s << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testcase; cin >> testcase;

	for (int tc = 1; tc <= testcase; tc++) {
		string s; cin >> s;
		solve(s);
	}
	return 0;
}
