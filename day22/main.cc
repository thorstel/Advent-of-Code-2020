#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

static deque<ull> read_cards()
{
	deque<ull> cards;
	string line;
	getline(cin, line);
	while (getline(cin, line)) {
		if (line.empty()) { break; }
		cards.emplace_back(stoll(line));
	}
	return cards;
}

static ull calc_score(const deque<ull>& winner)
{
	ull score = 0, val = 1;
	for (auto it = rbegin(winner); it != rend(winner); ++it, ++val) {
		score += (*it) * val;
	}
	return score;
}

template<int Part>
static pair<ull,ull> play_game(deque<ull> player1, deque<ull> player2)
{
	static_assert(Part == 1 || Part == 2);
	set<pair<deque<ull>,deque<ull>>> seen;
	while (!player1.empty() && !player2.empty()) {
		if (Part == 2 && !seen.emplace(make_pair(player1, player2)).second) {
			return make_pair(1, calc_score(player1));
		}
		ull c1 = player1.front();
		player1.pop_front();
		ull c2 = player2.front();
		player2.pop_front();
		ull winner = 0;
		if (Part == 2 && c1 <= player1.size() && c2 <= player2.size()) {
			winner = play_game<Part>(
					deque<ull>{begin(player1), begin(player1) + c1},
					deque<ull>{begin(player2), begin(player2) + c2}).first;
		} else {
			winner = (c1 > c2) ? 1 : 2;
		}
		if (winner == 1) {
			player1.push_back(c1);
			player1.push_back(c2);
		} else if (winner == 2) {
			player2.push_back(c2);
			player2.push_back(c1);
		} else { assert(false); }
	}
	return make_pair(
			player2.empty() ? 1 : 2,
			player2.empty() ? calc_score(player1) : calc_score(player2));
}

int main()
{
	auto player1 = read_cards();
	auto player2 = read_cards();
	cout << play_game<1>(player1, player2).second << endl;
	cout << play_game<2>(player1, player2).second << endl;
	return 0;
}
