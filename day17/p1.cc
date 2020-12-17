#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	vector<string> input {istream_iterator<string>{cin}, {}};

	ll ncycles = 6;
	ll nx = (2 * ncycles) + input[0].size();
	ll ny = (2 * ncycles) + input.size();
	ll nz = (2 * ncycles) + 1;
	vector<vector<vector<bool>>> grid(
			nz, vector<vector<bool>>(
				ny, vector<bool>(nx, false)));
	for (auto y = 0u; y < input.size(); ++y) {
		for (auto x = 0u; x < input[y].size(); ++x) {
			grid[ncycles][ncycles+y][ncycles+x] = input[y][x] == '#';
		}
	}

	auto count_neighbors = [&](ll x, ll y, ll z) {
		ll cnt = 0;
		for (ll iz = max(0ll, z-1); iz < min(z+2, nz); ++iz) {
			for (ll iy = max(0ll, y-1); iy < min(y+2, ny); ++iy) {
				for (ll ix = max(0ll, x-1); ix < min(x+2, nx); ++ix) {
					if (grid[iz][iy][ix]) {
						++cnt;
					}
				}
			}
		}
		if (grid[z][y][x]) { --cnt; }
		return cnt;
	};

	ll last_count = 0;
	for (ll cycle = 0; cycle < ncycles; ++cycle) {
		last_count = 0;
		auto new_grid = grid;
		for (ll z = 0; z < nz; ++z) {
			for (ll y = 0; y < ny; ++y) {
				for (ll x = 0; x < nx; ++x) {
					ll neighbors = count_neighbors(x, y, z);
					if (grid[z][y][x]) {
						new_grid[z][y][x] = (neighbors == 2) || (neighbors == 3);
					} else {
						new_grid[z][y][x] = (neighbors == 3);
					}
					if (new_grid[z][y][x]) { ++last_count; }
				}
			}
		}
		grid = move(new_grid);
	}

	cout << last_count << endl;
	return 0;
}
