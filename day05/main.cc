#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	string pass;
	vector<ll> ids;
	while (cin >> pass) {
		ll r1 = 0, r2 = 127;
		for (auto i = 0; i < 7; ++i) {
			if (pass[i] == 'F') {
				r2 -= ((r2 - r1 + 1) / 2);
			} else {
				assert(pass[i] == 'B');
				r1 += ((r2 - r1 + 1) / 2);
			}
		}
		assert(r1 == r2);
		ll c1 = 0, c2 = 7;
		for (auto i = 7; i < 10; ++i) {
			if (pass[i] == 'L') {
				c2 -= ((c2 - c1 + 1) / 2);
			} else {
				assert(pass[i] == 'R');
				c1 += ((c2 - c1 + 1) / 2);
			}
		}
		assert(c1 == c2);
		ids.push_back((r1 * 8) + c1);
	}
	sort(ids.begin(), ids.end());

	// Part 1
	cout << *max_element(ids.begin(), ids.end()) << endl;

	// Part 2
	for (auto i = 0u; i < ids.size() - 1; ++i) {
		if (ids[i] + 1 != ids[i+1]) {
			cout << (ids[i] + 1) << endl;
			break;
		}
	}
	return 0;
}
