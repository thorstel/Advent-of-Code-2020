#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	vector<string> grid(istream_iterator<string>(cin), {});
	auto count_trees = [&](auto right, auto down) -> ll {
		ll col = 0;
		ll cnt = 0;
		for (auto row = 0u; row < grid.size(); row += down) {
			if (grid[row][col] == '#') ++cnt;
			col = (col + right) % grid[0].size();
		}
		return cnt;
	};

	// Part 1
	cout << count_trees(3, 1) << endl;

	// Part 2
	cout << (
			count_trees(1, 1) *
			count_trees(3, 1) *
			count_trees(5, 1) *
			count_trees(7, 1) *
			count_trees(1, 2)
			) << endl;
	return 0;
}
