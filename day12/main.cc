#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr pair<ll,ll> move_forward(ll dir, ll val)
{
	switch (dir / 90) {
		case 0: return make_pair(0, val);
		case 1: return make_pair(val, 0);
		case 2: return make_pair(0, -val);
		case 3: return make_pair(-val, 0);
		default:
			assert(false);
			return make_pair(0, 0);
	}
}

int main()
{
	ll x = 0, y = 0, dir = 90; // Part 1 coordinates 
	ll sx = 0, sy = 0, wx = 10, wy = 1; // Part 2 coordinates
	char cmd;
	string param;
	while (cin >> cmd >> param) {
		ll val = stoi(param);
		switch (cmd) {
			case 'N':
				y += val; // Part 1
				wy += val; // Part 2
				break;
			case 'E':
				x += val; // Part 1
				wx += val; // Part 2
				break;
			case 'S':
				y -= val; // Part 1
				wy -= val; // Part 2
				break;
			case 'W':
				x -= val; // Part 1
				wx -= val; // Part 2
				break;
			case 'L':
				dir = (dir - val + 360) % 360; // Part 1
				while (val > 0) { // Part 2
					swap(wx, wy);
					wx = -wx;
					val -= 90;
				}
				break;
			case 'R':
				dir = (dir + val) % 360; // Part 1
				while (val > 0) { // Part 2
					swap(wx, wy);
					wy = -wy;
					val -= 90;
				}
				break;
			case 'F': {
				// Part 1
				auto [dx, dy] = move_forward(dir, val);
				x += dx;
				y += dy;
				// Part 2
				sx += val * wx;
				sy += val * wy;
				break;
			}
			default:
				assert(false);
				break;
		}
	}
	cout << abs(x) + abs(y) << endl; // Part 1
	cout << abs(sx) + abs(sy) << endl; // Part 2
	return 0;
}
