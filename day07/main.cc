#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static unordered_map<string, unordered_map<string, ll>> contained_in;

static ll count_bags(const string& bag)
{
	ll cnt = 0;
	for (auto& [k, v] : contained_in[bag]) {
		cnt += (v * count_bags(k)) + v;
	}
	return cnt;
}

int main()
{
	regex pat1(R"((\w+ \w+) bags? contain)");
	regex pat2(R"((\d+) (\w+ \w+) bags?(,|.))");
	unordered_map<string, unordered_set<string>> contained_by;
	string line;
	while (getline(cin, line)) {
		smatch m;
		bool found = regex_search(line, m, pat1);
		assert(found);
		contained_in.emplace(m[1], unordered_map<string, ll>());
		for (auto it = sregex_iterator(line.begin(), line.end(), pat2); it != sregex_iterator(); ++it) {
			if (!contained_by.emplace((*it)[2], unordered_set<string>({m[1]})).second) {
				contained_by[(*it)[2]].insert(m[1]);
			}
			contained_in[m[1]].emplace((*it)[2], stoi((*it)[1]));
		}
	}

	deque<string> q({"shiny gold"});
	unordered_set<string> seen({"shiny gold"});
	while (!q.empty()) {
		for (auto& bag : contained_by[q.front()]) {
			if (seen.insert(bag).second) {
				q.push_back(bag);
			}
		}
		q.pop_front();
	}

	cout << seen.size() - 1 << endl; // do not count self
	cout << count_bags("shiny gold") << endl;
	return 0;
}
