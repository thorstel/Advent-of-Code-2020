#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define sz(X) ((long long)(X).size())

static array<ll, 1'000'001> cups; // Unused index 0 so that cup no. == array index
static constexpr ll choose_dst(ll dst, ll last_cup) { return dst > 1 ? dst - 1 : last_cup; }
static constexpr ll cup_id(char c) { return c - '0'; }

void play_game(const string& input, ll num_cups, ll num_rounds)
{
	assert(num_cups < sz(cups));
	ll last_id = sz(cups) - 1, max_id = 0;
	for (char c : input) {
		ll id = cup_id(c);
		cups[last_id] = id;
		last_id = id;
		max_id = max(id, max_id);
	}
	if (num_cups == sz(input)) {
		cups[cup_id(input.back())] = cup_id(input[0]);
	} else {
		++max_id;
		cups[cup_id(input.back())] = max_id;
		iota(begin(cups) + max_id, end(cups) - 1, max_id + 1);
	}

	ll current = cup_id(input[0]);
	for (ll i = 0; i < num_rounds; ++i) {
		ll cup1 = cups[current];
		ll cup2 = cups[cup1];
		ll cup3 = cups[cup2];
		ll dst = choose_dst(current, num_cups);
		while (dst == cup1 || dst == cup2 || dst == cup3) {
			dst = choose_dst(dst, num_cups);
		}
		cups[current] = cups[cup3];
		cups[cup3] = cups[dst];
		cups[dst] = cup1;
		current = cups[current];
	}
}

int main()
{
	string input;
	cin >> input;

	// Part 1
	play_game(input, sz(input), 100);
	ll c = cups[1];
	for (ll _ = 0; _ < sz(input) - 1; ++_) {
		cout << c;
		c = cups[c];
	}
	cout << endl;

	// Part 2
	play_game(input, 1'000'000, 10'000'000);
	cout << (cups[1] * cups[cups[1]]) << endl;
	return 0;
}
