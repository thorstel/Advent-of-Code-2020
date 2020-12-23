#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

struct Cup
{
	ull id;
	Cup *next;
};

vector<Cup> play_game(const string& input, ull num_cups, ull num_rounds)
{
	assert(num_cups >= input.size());
	auto choose_dst = [&](ull dst) { return (dst == 1) ? num_cups : (dst - 1); };

	vector<Cup> cups(num_cups);
	for (ull i = 0; i < cups.size(); ++i) {
		cups[i].id = (i + 1);
		if (i < cups.size() - 1) {
			cups[i].next = &cups[i + 1];
		}
	}

	ull last_id = num_cups, max_id = 0;
	for (char c : input) {
		ull id = c - '0';
		cups[last_id - 1].next = &cups[id - 1];
		last_id = id;
		max_id = max(max_id, id);
	}

	auto *current = &cups[input[0] - '0' - 1];
	if (input.size() == num_cups) {
		cups[last_id - 1].next = current;
	} else {
		cups[last_id - 1].next = &cups[max_id];
	}

	for (ull i = 0; i < num_rounds; ++i) {
		auto *cup1 = current->next;
		auto *cup2 = cup1->next;
		auto *cup3 = cup2->next;
		ull dst = choose_dst(current->id);
		while (dst == cup1->id || dst == cup2->id || dst == cup3->id) {
			dst = choose_dst(dst);
		}
		auto *dst_cup = &cups[dst - 1];
		current->next = cup3->next;
		cup3->next = dst_cup->next;
		dst_cup->next = cup1;
		current = current->next;
	}
	return cups;
}

int main()
{
	string input;
	cin >> input;

	// Part 1
	auto cups = play_game(input, input.size(), 100);
	auto *current = &cups[0];
	for (auto i = 0u; i < cups.size() - 1; ++i) {
		current = current->next;
		cout << current->id;
	}
	cout << endl;

	// Part 2
	cups = play_game(input, 1'000'000, 10'000'000);
	cout << (cups[0].next->id) * (cups[0].next->next->id) << endl;
	return 0;
}
