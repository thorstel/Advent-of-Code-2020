#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	ll turn = 0, num = 0;
	unordered_map<ll,ll> last_spoken;
	bool init = false;
	string s;
	while (getline(cin, s, ',')) {
		ll x = stoll(s);
		if (init) { last_spoken[num] = turn; }
		else { init = true; }
		num = x;
		++turn;
	}
	for (; turn < 30000000; ++turn) {
		if (turn == 2020) {
			cout << num << endl; // Part 1
		}
		auto [it, is_new] = last_spoken.emplace(num, turn);
		if (is_new) {
			num = 0;
		} else {
			num = turn - it->second;
			it->second = turn;
		}
	}
	cout << num << endl;
	return 0;
}
