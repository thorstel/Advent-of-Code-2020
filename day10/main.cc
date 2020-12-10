#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static deque<ll> numbers;
static unordered_map<ll,ll> seen;

static ll count_ways(ll i)
{
	if (i >= ll(numbers.size() - 1)) {
		return 1;
	}
	if (seen.find(i) != seen.end()) {
		return seen[i];
	}
	ll cnt = 0;
	for (ll j = i+1; j < min(i+4, ll(numbers.size())); ++j) {
		if (numbers[j] - numbers[i] < 4) {
			cnt += count_ways(j);
		}
	}
	seen[i] = cnt;
	return cnt;
}

int main()
{
	numbers.insert(numbers.end(), istream_iterator<ll>{cin}, {});
	sort(numbers.begin(), numbers.end());
	numbers.push_front(0);
	numbers.push_back(numbers.back() + 3);
	ll cnt1 = 0, cnt3 = 0;
	for (ll i = 0; i < ll(numbers.size() - 1); ++i) {
		ll diff = numbers[i+1] - numbers[i];
		if (diff == 1) { ++cnt1; }
		else if (diff == 3) { ++cnt3; }
	}
	cout << (cnt1 * cnt3) << endl;
	cout << count_ways(0) << endl;
	return 0;
}
