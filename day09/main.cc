#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	vector<ll> numbers {istream_iterator<ll>(cin), {}};

	// Part 1
	ll p1 = 0;
	for (auto i = 25u; i < numbers.size(); ++i) {
		bool found = false;
		for (auto j = i-25; j < i-1; ++j) {
			for (auto k = j+1; k < i; ++k) {
				if (numbers[j] + numbers[k] == numbers[i]) {
					found = true;
				}
			}
		}
		if (!found) {
			p1 = numbers[i];
			break;
		}
	}
	cout << p1 << endl;

	// Part 2
	for (auto i = 0u; i < numbers.size(); ++i) {
		ll x = numbers[i], p2min = x, p2max = x;
		for (auto j = i+1; j < numbers.size(); ++j) {
			p2min = min(p2min, numbers[j]);
			p2max = max(p2max, numbers[j]);
			x += numbers[j];
			if (x > p1) { break; }
			if (x == p1) {
				cout << p2min + p2max << endl;
				return 0;
			}
		}
	}
	return 0;
}
