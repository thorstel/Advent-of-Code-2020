#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

static vector<string> rotate_tile(const vector<string>& tile)
{
	vector<string> rotated;
	for (ull col = 0u; col < tile[0].size(); ++col) {
		stringstream ss;
		for (ll row = tile.size() - 1; row >= 0; --row) {
			ss << tile[row][col];
		}
		rotated.emplace_back(ss.str());
	}
	return rotated;
}

static vector<string> flip_tile(const vector<string>& tile)
{
	vector<string> flipped;
	for (ll row = tile.size() - 1; row >= 0; --row) {
		flipped.push_back(tile[row]);
	}
	return flipped;
}

//    0
//   ┌─┐
// 3 │ │ 1
//   └─┘
//    2
static string get_side(const vector<string>& tile, ll side)
{
	stringstream ss;
	switch (side) {
		case 0:
			return tile.front();
		case 1:
			for (const string& row : tile) { ss << row.back(); }
			break;
		case 2:
			return tile.back();
		case 3:
			for (const string& row : tile) { ss << row.front(); }
			break;
		default:
			assert(false);
			break;
	}
	return ss.str();
}

// global because I am lazy...
static unordered_map<ll,vector<vector<string>>> tiles;

static vector<vector<string>> get_orientations(const vector<string>& orig_tile)
{
	vector<vector<string>> orientations {orig_tile};
	orientations.emplace_back(rotate_tile(orientations.back()));
	orientations.emplace_back(rotate_tile(orientations.back()));
	orientations.emplace_back(rotate_tile(orientations.back()));
	orientations.emplace_back(flip_tile(orientations.back()));
	orientations.emplace_back(rotate_tile(orientations.back()));
	orientations.emplace_back(rotate_tile(orientations.back()));
	orientations.emplace_back(rotate_tile(orientations.back()));
	return orientations;
}

static vector<vector<pair<ll,ll>>> grid;
static unordered_set<ll> seen;

static bool fill_grid(ull row, ull col)
{
	if (row >= grid.size()) { return true; }
	if (col >= grid[row].size()) { return fill_grid(row + 1u, 0u); }
	for (auto& [id, orient] : tiles) {
		if (seen.find(id) != end(seen)) { continue; }
		for (ull i = 0u; i < orient.size(); ++i) {
			bool fits = true;
			if (row > 0) {
				auto [other, j] = grid[row - 1][col];
				if (get_side(tiles[other][j], 2) != get_side(orient[i], 0)) {
					fits = false;
				}
			}
			if (col > 0) {
				auto [other, j] = grid[row][col - 1];
				if (get_side(tiles[other][j], 1) != get_side(orient[i], 3)) {
					fits = false;
				}
			}
			if (fits) {
				grid[row][col] = make_pair(id, i);
				seen.insert(id);
				if (fill_grid(row, col + 1u)) { return true; }
				seen.erase(id);
			}
		}
	}
	return false;
}

int main()
{
	// Parse input
	string line;
	while (getline(cin, line)) {
		stringstream ss {line};
		string s;
		ll id;
		ss >> s >> id;
		vector<string> tile;
		while (getline(cin, line)) {
			if (line.empty()) { break; }
			tile.emplace_back(move(line));
		}

		tiles.emplace(id, move(get_orientations(tile)));
	}

	// Identify the 4 corner tiles.
	optional<ll> top_left;
	vector<ll> corner_tiles;
	for (auto& [id, tile] : tiles) {
		unordered_set<ll> neighbors;
		for (ll s = 0; s < 4; ++s) {
			[&] { // I feel dirty breaking the (middle) loop like that 😬
				string side = get_side(tile.front(), s);
				for (auto& [oth_id, orient] : tiles) {
					if (id == oth_id) { continue; }
					for (auto& oth_tile : orient) {
						string oth_side = get_side(oth_tile, (s + 2) % 4);
						if (side == oth_side) {
							neighbors.insert(s);
							return;
						}
					}
				}
			}();
		}
		if (neighbors.size() == 2) {
			corner_tiles.push_back(id);
			if ((neighbors.find(1) != end(neighbors)) && (neighbors.find(2) != end(neighbors))) {
				// The top-left corner has neighboring tiles to the right and bottom.
				// There must only be a single tile fulfilling these criteria.
				assert(!top_left);
				top_left = id;
			}
		}
		else if (neighbors.size() < 2) { assert(false); }
	}
	assert(corner_tiles.size() == 4u);

	// Answer for part 1
	cout << accumulate(begin(corner_tiles), end(corner_tiles), 1ll, multiplies<ll>{}) << endl;

	// Perform depth-first-search to get a valid grid.
	// Note: This also works without identifying the top-left corner first (with
	// fill_grid(0u, 0u) instead). However, the DFS takes quite a bit longer to
	// come up with a solution.
	ull N = ull(sqrt(tiles.size()));
	assert((N * N) == tiles.size());
	grid = vector<vector<pair<ll,ll>>>(N, vector<pair<ll,ll>>(N, pair<ll,ll>{}));
	grid[0][0] = make_pair(*top_left, 0);
	seen.insert(*top_left);
	if (!fill_grid(0u, 1u)) { assert(false); }

	// Build the image without borders
	vector<string> image;
	for (ull r = 0u; r < grid.size(); ++r) {
		ull num = tiles[grid[r][0].first][0].size();
		for (ull i = 1u; i < (num - 1u); ++i) {
			stringstream ss;
			for (ull c = 0u; c < grid[r].size(); ++c) {
				auto [id, ori] = grid[r][c];
				ss << tiles[id][ori][i].substr(1, (num - 2));
			}
			image.emplace_back(ss.str());
		}
	}

	const vector<string> monster {
		"                  # ",
		"#    ##    ##    ###",
		" #  #  #  #  #  #   "
	};
	vector<pair<ull,ull>> mon_offsets;
	ull maxr = 0, maxc = 0;
	for (ull r = 0; r < monster.size(); ++r) {
		for (ull c = 0; c < monster[r].size(); ++c) {
			if (monster[r][c] == '#') {
				mon_offsets.emplace_back(make_pair(r, c));
				maxr = max(maxr, r);
				maxc = max(maxc, c);
			}
		}
	}

	// Find the sea monsters for Part 2
	for (const auto& img : get_orientations(image)) {
		set<pair<ull,ull>> mon_coords;
		for (ull r = 0u; r < (img.size() - maxr); ++r) {
			for (ull c = 0u; c < (img[r].size() - maxc); ++c) {
				auto match_mon = [&](auto& p) { return img[r + p.first][c + p.second] == '#'; };
				if (all_of(begin(mon_offsets), end(mon_offsets), match_mon)) {
					for (auto [dr, dc] : mon_offsets) {
						mon_coords.insert(make_pair(r + dr, c + dc));
					}
				}
			}
		}
		if (mon_coords.size() > 0u) {
			auto roughness = [](auto p, const auto& s) { return p + count(begin(s), end(s), '#'); };
			cout << (accumulate(begin(img), end(img), 0ull, roughness) - mon_coords.size()) << endl;
		}
	}
	return 0;
}
