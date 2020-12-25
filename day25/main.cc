#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	ll card_key, door_key;
	cin >> card_key >> door_key;

	ll loop_size = 0, val = 1;
	while (val != card_key) {
		val = (val * 7) % 20201227;
		++loop_size;
	}

	val = 1;
	for (ll i = 0; i < loop_size; ++i) {
		val = (val * door_key) % 20201227;
	}
	cout << val << endl;
	return 0;
}
