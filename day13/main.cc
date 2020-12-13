#include <bits/stdc++.h>

using namespace std;
using ll = long long;

tuple<ll,ll,ll> extended_gcd(ll a, ll b)
{
	if (a == 0) { return make_tuple(b, 0, 1); }
	auto [gcdiv, x, y] = extended_gcd(b % a, a);
	return make_tuple(gcdiv, y - ((b / a) * x), x);
}

int main()
{
	ll ts;
	cin >> ts;
	string s;
	ll min_diff = INT_MAX, p1_result = 0, offset = 0;
	vector<ll> a, m;
	while (getline(cin, s, ',')) {
		if (s[0] != 'x') { 
			ll id = stoi(s);
			assert(ts % id); // does not work if evenly divisible
			ll diff = id - (ts % id);
			if (diff < min_diff) {
				min_diff = diff;
				p1_result = id * diff;
			}
			// Part 2: x = a[i] (mod m[i]) = id - offset (mod id)
			a.push_back(id - (offset % id));
			m.push_back(id);
		}
		++offset;
	}
	cout << p1_result << endl;

	// https://crypto.stanford.edu/pbc/notes/numbertheory/crt.html
	ll M = accumulate(begin(m), end(m), 1ll, multiplies<ll>());
	ll x = 0;
	for (auto i = 0u; i < m.size(); ++i) {
		ll b = M / m[i];
		auto [gcdiv, b_inv, _] = extended_gcd(b, m[i]);
		assert(gcdiv == 1);
		x = (M + x + (a[i] * b * b_inv)) % M;
	}
	cout << x << endl;
	return 0;
}
