#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	vector<ll> input(istream_iterator<ll>(cin), {});
	for (auto i = 0u; i < input.size(); ++i) {
		for (auto j = i+1; j < input.size(); ++j) {
			if (input[i] + input[j] == 2020) {
				cout << (input[i] * input[j]) << endl;
				return 0;
			}
		}
	}
	return 0;
}
