#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

static unordered_map<string,tuple<ll,ll,ll,ll>> rules;

static bool is_valid(const string& rule, ll val)
{
	auto [l1, u1, l2, u2] = rules[rule];
	return (val >= l1 && val <= u1) || (val >= l2 && val <= u2);
}

static vector<ll> parse_ticket(string& line)
{
	vector<ll> ticket;
	stringstream ss {line};
	string s;
	while (getline(ss, s, ',')) { ticket.push_back(stoll(s)); }
	return ticket;
}

int main()
{
	regex rule_pattern {R"((.*): (\d+)-(\d+) or (\d+)-(\d+))"};
	string line;
	while (getline(cin, line)) {
		if (line.empty()) { break; }
		smatch match;
		if (!regex_match(line, match, rule_pattern)) { assert(false); }
		rules[match[1]] = make_tuple(stoll(match[2]), stoll(match[3]), stoll(match[4]), stoll(match[5]));
	}
	getline(cin, line); // == "your ticket:"
	getline(cin, line); // == [ticket contents]
	auto your_ticket = parse_ticket(line);
	getline(cin, line); // == [empty line]
	getline(cin, line); // == "nearby tickets:"

	ll error_rate = 0;
	vector<vector<ll>> tickets;
	while (getline(cin, line)) {
		auto ticket = parse_ticket(line);
		bool valid = true;
		for (ll val : ticket) {
			auto valid_value = [&](auto& kv) { return is_valid(kv.first, val); };
			if (none_of(begin(rules), end(rules), valid_value)) {
				error_rate += val;
				valid = false;
			}
		}
		if (valid) {
			tickets.push_back(move(ticket));
		}
	}
	cout << error_rate << endl;

	unordered_map<string, ull> assigned_rules;
	unordered_set<string> unassinged_rules;
	for (auto& kv : rules) { unassinged_rules.insert(kv.first); }

	while (assigned_rules.size() < rules.size()) {
		for (ull col = 0u; col < your_ticket.size(); ++col) {
			vector<string> matching;
			for (auto& rule : unassinged_rules) {
				auto valid_col = [&](auto& ticket) { return is_valid(rule, ticket[col]); };
				if (all_of(begin(tickets), end(tickets), valid_col)) {
					matching.push_back(rule);
				}
			}
			if (matching.size() == 1u) {
				unassinged_rules.erase(matching[0]);
				assigned_rules[matching[0]] = col;
			}
		}
	}

	ll part2 = 1;
	for (auto& [rule, col] : assigned_rules) {
		if (rule.find("departure") != string::npos) {
			part2 *= your_ticket[col];
		}
	}
	cout << part2 << endl;
	return 0;
}
