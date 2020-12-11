#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static const vector<pair<ll,ll>> deltas {
	{-1, -1}, {-1, 0}, {-1, 1},
	{ 0, -1},          { 0, 1},
	{ 1, -1}, { 1, 0}, { 1, 1}
};

template<int Part>
static vector<string> mutate(const vector<string>& old)
{
	static_assert(Part == 1 || Part == 2);
	vector<string> grid = old;
	ll nrow = old.size(), ncol = old[0].size();
	for (ll r = 0; r < nrow; ++r) {
		for (ll c = 0; c < ncol; ++c) {
			if (old[r][c] == '.') { continue; }
			ll cnt = 0;
			for (auto [dr, dc] : deltas) {
				ll rn = r + dr;
				ll cn = c + dc;
				if (Part == 1) {
					if (rn >= 0 && rn < nrow && cn >= 0 && cn < ncol) {
						if (old[rn][cn] == '#') { ++cnt; }
					}
				} else {
					while (rn >= 0 && rn < nrow && cn >= 0 && cn < ncol) {
						if (old[rn][cn] == '#') {
							++cnt;
							break;
						} else if (old[rn][cn] == 'L') { break; }
						rn += dr;
						cn += dc;
					}
				}
			}
			if (old[r][c] == 'L' && cnt == 0) {
				grid[r][c] = '#';
			} else if (old[r][c] == '#' && cnt >= (Part == 1 ? 4 : 5)) {
				grid[r][c] = 'L';
			}
		}
	}
	return grid;
}

int main()
{
	vector<string> grid1 {istream_iterator<string>{cin}, {}}, grid2 {grid1};
	optional<ll> cnt1, cnt2;
	auto num_seats = [](ll n, string& s) { return n + count(s.begin(), s.end(), '#'); };
	while (!cnt1 || !cnt2) {
		if (!cnt1) {
			auto new_grid = mutate<1>(grid1);
			if (new_grid == grid1) {
				cnt1 = accumulate(new_grid.begin(), new_grid.end(), 0, num_seats);
			}
			grid1 = new_grid;
		}
		if (!cnt2) {
			auto new_grid = mutate<2>(grid2);
			if (new_grid == grid2) {
				cnt2 = accumulate(new_grid.begin(), new_grid.end(), 0, num_seats);
			}
			grid2 = new_grid;
		}
	}
	cout << *cnt1 << endl;
	cout << *cnt2 << endl;
	return 0;
}
