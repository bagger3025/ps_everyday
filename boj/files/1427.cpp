#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	char c;
	int cnt[10] = { 0 };
	while (cin >> c) {
		cnt[c - '0']++;
	}
	for (int i = 9; i >= 0; i--) {
		while (cnt[i]--) {
			cout << i;
		}
	}
}
