#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	string line;
	ll cnt1 = 0, cnt2 = 0;
	unordered_set<char> seen1;
	string seen2;
	bool init = true;
	while (getline(cin, line)) {
		if (line.empty()) {
			cnt1 += seen1.size();
			cnt2 += seen2.size();
			seen1.clear();
			init = true;
			continue;
		}
		seen1.insert(line.begin(), line.end());
		if (init) {
			seen2 = line;
			init = false;
		} else {
			seen2.erase(
					remove_if(seen2.begin(), seen2.end(),
						[&](char c) { return line.find(c) == string::npos; }),
					seen2.end());
		}
	}
	cnt1 += seen1.size();
	cnt2 += seen2.size();
	cout << cnt1 << endl;
	cout << cnt2 << endl;
	return 0;
}
