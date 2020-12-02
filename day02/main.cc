#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
	regex pat(R"((\d+)-(\d+) (\w): (\w+))");
	string line;
	ll valid1 = 0;
	ll valid2 = 0;

	while (getline(cin, line)) {
		smatch match;
		if (!regex_match(line, match, pat)) {
			cout << "ERROR\n";
			return 1;
		}

		ll x = stoi(match[1]);
		ll y = stoi(match[2]);
		char c = match[3].str()[0];
		string pw = match[4];

		// Part 1
		ll cnt = count(pw.begin(), pw.end(), c);
		if (cnt >= x && cnt <= y) ++valid1;

		// Part 2
		if ((pw[x-1] == c) != (pw[y-1] == c)) ++valid2;
	}

	cout << valid1 << endl;
	cout << valid2 << endl;
	return 0;
}
