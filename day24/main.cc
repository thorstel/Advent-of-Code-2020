#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// https://www.redblobgames.com/grids/hexagons/#coordinates-offset
static const map<string,pair<ll,ll>> offsets {
	{"e", { 1, 0}}, {"se", { 1,  1}}, {"sw", { 0,  1}},
	{"w", {-1, 0}}, {"nw", {-1, -1}}, {"ne", { 0, -1}}
};

int main()
{
	map<pair<ll,ll>,bool> black_tiles;
	for (string line; getline(cin, line);) {
		ll x = 0, y = 0;
		for (auto i = 0u; i < line.size();) {
			if (auto it = offsets.find(line.substr(i, 1)); it != end(offsets)) {
				auto [dx, dy] = (*it).second;
				x += dx;
				y += dy;
				i += 1;
			} else if (auto it = offsets.find(line.substr(i, 2)); it != end(offsets)) {
				auto [dx, dy] = (*it).second;
				x += dx;
				y += dy;
				i += 2;
			} else { assert(false); }
		}
		auto pos = make_pair(x, y);
		black_tiles[pos] = !black_tiles[pos];
	}
	auto is_black = [](auto& kv) { return kv.second; };
	cout << count_if(begin(black_tiles), end(black_tiles), is_black) << endl;

	for (ll i = 0; i < 100; ++i) {
		// To create the next generation we only have to consider the
		// tiles that are currently black and their direct neighbors.
		map<pair<ll,ll>,bool> next_gen;
		for (auto& [pos, black] : black_tiles) {
			if (black) {
				next_gen[pos] = true;
				for (auto& offset : offsets) {
					auto [dx, dy] = offset.second;
					auto adj = make_pair(pos.first + dx, pos.second + dy);
					next_gen.emplace(adj, false); // will not overwrite if already black
				}
			}
		}
		for (auto& [pos, black] : next_gen) {
			ll cnt = 0;
			for (auto& offset : offsets) {
				auto [dx, dy] = offset.second;
				auto adj = make_pair(pos.first + dx, pos.second + dy);
				if (black_tiles[adj]) { ++cnt; }
			}
			if (black) {
				next_gen[pos] = (cnt > 0) && (cnt <= 2);
			} else {
				next_gen[pos] = (cnt == 2);
			}
		}
		black_tiles = move(next_gen);
	}
	cout << count_if(begin(black_tiles), end(black_tiles), is_black) << endl;
	return 0;
}
