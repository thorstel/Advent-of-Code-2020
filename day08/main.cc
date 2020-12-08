#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vec = vector<pair<string,ll>>;

static pair<ll,bool> run(const vec& prog)
{
	ll acc = 0;
	unordered_set<ll> seen;
	auto pc = 0u;
	while (pc < prog.size()) {
		if (!seen.insert(pc).second) {
			return make_pair(acc, false);
		}
		if (prog[pc].first == "acc") {
			acc += prog[pc].second;
			++pc;
		} else if (prog[pc].first == "jmp") {
			pc += prog[pc].second;
		} else {
			++pc;
		}
	}
	return make_pair(acc, true);
}

int main()
{
	string s;
	ll x;
	vec prog;
	while (cin >> s >> x) {
		prog.push_back(make_pair(s, x));
	}

	// Part 1
	cout << run(prog).first << endl;

	// Part 2
	unordered_map<string,string> fix {{"jmp", "nop"}, {"nop", "jmp"}};
	for (auto i = 0u; i < prog.size(); ++i) {
		if (prog[i].first == "nop" || prog[i].first == "jmp") {
			prog[i].first = fix[prog[i].first];
			auto res = run(prog);
			if (res.second) {
				cout << res.first << endl;
				break;
			}
			prog[i].first = fix[prog[i].first];
		}
	}
	return 0;
}
