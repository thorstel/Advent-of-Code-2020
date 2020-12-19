#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static string rulestr(string&& term)
{
	stringstream ssin {term}, ssout;
	string s;
	while (ssin >> s) { ssout << "(" + s + ")"; }
	return ssout.str();
}

static regex compile_regex(
		string target,
		unordered_map<string,string> terminal_rules,
		unordered_map<string,string> unresolved_rules)
{
	regex id_pattern {R"(\((\d+)\))"};
	while (!unresolved_rules.empty()) {
		auto rule_it = begin(unresolved_rules);
		while (rule_it != end(unresolved_rules)) {
			auto reg_it = sregex_iterator(begin(rule_it->second), end(rule_it->second), id_pattern);
			if (reg_it == sregex_iterator()) {
				terminal_rules.insert(*rule_it);
				rule_it = unresolved_rules.erase(rule_it);
			} else {
				for (; reg_it != sregex_iterator(); ++reg_it) {
					string id = (*reg_it)[1];
					if (auto kv = terminal_rules.find(id); kv != end(terminal_rules)) {
						string match = (*reg_it)[0];
						auto pos = rule_it->second.find(match);
						rule_it->second.replace(pos, match.size(), kv->second);
						break;
					}
				}
				++rule_it;
			}
		}
	}

	return regex {terminal_rules[target], regex::nosubs|regex::optimize};
}

int main()
{
	regex terminal_pattern {R"((\d+): "(\w)\")"};
	regex disjunct_pattern {R"((\d+): (.*) \| (.*))"};
	regex rule_pattern {R"((\d+): (.*))"};

	unordered_map<string,string> terminal_rules;
	unordered_map<string,string> unresolved_rules;
	string line;
	while (getline(cin, line)) {
		if (line.empty()) { break; }
		smatch match;
		if (regex_match(line, match, terminal_pattern)) {
			terminal_rules.emplace(match[1], match[2]);
		} else if (regex_match(line, match, disjunct_pattern)) {
			string rule = "((" + rulestr(match[2]) + ")|(" + rulestr(match[3]) + "))";
			unresolved_rules.emplace(match[1], rule);
		} else if (regex_match(line, match, rule_pattern)) {
			string rule = "(" + rulestr(match[2]) + ")";
			unresolved_rules.emplace(match[1], rule);
		} else { assert(false); }
	}
	auto p1_regex = compile_regex("0", terminal_rules, unresolved_rules);

	// Dirty hack for part 2: simply repeat the pattern 5 times
	unresolved_rules["8"] = "((42)|((42)(42))|((42)(42)(42))|((42)(42)(42)(42))|((42)(42)(42)(42)(42)))";
	unresolved_rules["11"] = "(((42)(31))|((42)(42)(31)(31))|((42)(42)(42)(31)(31)(31))|((42)(42)(42)(42)(31)(31)(31)(31))|((42)(42)(42)(42)(42)(31)(31)(31)(31)(31)))";
	auto p2_regex = compile_regex("0", terminal_rules, unresolved_rules);

	ll cnt1 = 0, cnt2 = 0;
	while (getline(cin, line)) {
		smatch match;
		if (regex_match(line, match, p1_regex)) { ++cnt1; }
		if (regex_match(line, match, p2_regex)) { ++cnt2; }
	}
	cout << cnt1 << endl;
	cout << cnt2 << endl;
	return 0;
}
