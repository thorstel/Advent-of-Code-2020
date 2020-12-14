#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

int main()
{
	regex mask_pattern {R"(mask = (\w+))"};
	regex mem_pattern {R"(mem\[(\d+)\] = (\d+))"};
	ull mask0 = 0u, mask1 = 0u;
	unordered_map<ull,ull> mem1, mem2;
	vector<int> float_bits;
	string line;
	while (getline(cin, line)) {
		smatch match;
		if (regex_match(line, match, mask_pattern)) {
			bitset<36> tmp0, tmp1;
			string mask = match[1];
			assert(mask.size() == 36u);
			float_bits.clear();
			for (auto i = 0; i < 36; ++i) {
				tmp0[i] = mask[35-i] != '0';
				tmp1[i] = mask[35-i] == '1';
				if (mask[35-i] == 'X') {
					float_bits.push_back(i);
				}
			}
			mask0 = tmp0.to_ullong();
			mask1 = tmp1.to_ullong();
		} else if (regex_match(line, match, mem_pattern)) {
			ull addr = stoull(match[1]);
			ull val1 = stoull(match[2]), val2 = val1;
			// Part 1
			val1 &= mask0;
			val1 |= mask1;
			mem1[addr] = val1;
			// Part 2
			addr |= mask1;
			for (ull bits = 0u; bits < (1u << float_bits.size()); ++bits) {
				bitset<36> addr_bits {addr};
				for (auto i = 0u; i < float_bits.size(); ++i) {
					addr_bits[float_bits[i]] = (bits & (1u << i)) != 0;
				}
				mem2[addr_bits.to_ullong()] = val2;
			}
		} else { assert(false); }
	}

	auto add_vals = [](ull p, auto& kv) { return p + kv.second; };
	cout << accumulate(begin(mem1), end(mem1), 0ull, add_vals) << endl;
	cout << accumulate(begin(mem2), end(mem2), 0ull, add_vals) << endl;
	return 0;
}
