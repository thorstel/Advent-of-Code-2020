#include <bits/stdc++.h>

using namespace std;

int main()
{
	multiset<string> safe_appearances;
	map<string,set<string>> allergens;
	const auto aoffset = string{"(contains "}.size();
	string line;
	while (getline(cin, line)) {
		string ingr, allg;
		if (auto pos = line.find('('); pos != string::npos) {
			ingr = line.substr(0, pos - 1);
			allg = line.substr((pos + aoffset), (line.size() - pos - aoffset - 1));
			allg.erase(remove(begin(allg), end(allg), ','), end(allg));
		} else {
			ingr = line;
		}

		set<string> ingredients;
		stringstream ss {ingr};
		string s;
		while (ss >> s) {
			ingredients.insert(s);
			safe_appearances.insert(s);
		}

		ss = stringstream{allg};
		while (ss >> s) {
			auto [kv, is_new] = allergens.emplace(s, ingredients);
			if (!is_new) {
				set<string> intersect;
				set_intersection(
						begin(ingredients), end(ingredients),
						begin(kv->second), end(kv->second),
						inserter(intersect, begin(intersect)));
				kv->second = move(intersect);
			}
		}
	}

	// Part 1
	for (auto& kv : allergens) {
		for (auto& allg : kv.second) {
			safe_appearances.erase(allg);
		}
	}
	cout << safe_appearances.size() << endl;

	// Part 2
	while (any_of(begin(allergens), end(allergens), [](auto& kv) { return kv.second.size() > 1; })) {
		for (auto& kv : allergens) {
			if (kv.second.size() == 1) {
				string elem = *begin(kv.second);
				for (auto& other : allergens) {
					if (kv.first != other.first) {
						other.second.erase(elem);
					}
				}
			}
		}
	}
	for (auto& kv : allergens) { cout << *begin(kv.second) << ","; }
	cout << endl;
	return 0;
}
