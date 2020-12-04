#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static bool byr(string& pw)
{
	static regex pat(R"( byr:(\d{4}) )");
	smatch m;
	if (regex_search(pw, m, pat)) {
		ll y = stoi(m[1]);
		return y >= 1920 && y <= 2002;
	}
	return false;
}

static bool iyr(string& pw)
{
	static regex pat(R"( iyr:(\d{4}) )");
	smatch m;
	if (regex_search(pw, m, pat)) {
		ll y = stoi(m[1]);
		return y >= 2010 && y <= 2020;
	}
	return false;
}

static bool eyr(string& pw)
{
	static regex pat(R"( eyr:(\d{4}) )");
	smatch m;
	if (regex_search(pw, m, pat)) {
		ll y = stoi(m[1]);
		return y >= 2020 && y <= 2030;
	}
	return false;
}

static bool hgt(string& pw)
{
	static regex pat(R"( hgt:(\d+)(cm|in) )");
	smatch m;
	if (regex_search(pw, m, pat)) {
		ll h = stoi(m[1]);
		if (m[2] == "cm") return h >= 150 && h <= 193;
		else return h >= 59 && h <= 76;
	}
	return false;
}

static bool hcl(string& pw)
{
	static regex pat(R"( hcl:#\w{6} )");
	smatch m;
	return regex_search(pw, m, pat);
}

static bool ecl(string& pw)
{
	static regex pat(R"( ecl:(amb|blu|brn|gry|grn|hzl|oth) )");
	smatch m;
	return regex_search(pw, m, pat);
}

static bool pid(string& pw)
{
	static regex pat(R"( pid:\d{9} )");
	smatch m;
	return regex_search(pw, m, pat);
}

int main()
{
	auto fields = {"byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:"};
	string line;
	stringstream ss;
	ll valid1 = 0, valid2 = 0;
	auto check = [&] {
		string pw = ss.str();
		ss.str(string());

		// Part 1
		if (all_of(fields.begin(), fields.end(), [&](auto& f) { return pw.find(f) != string::npos; })) { 
			++valid1;
		}

		// Part 2
		if (byr(pw) && iyr(pw) && eyr(pw) && hgt(pw) && hcl(pw) && ecl(pw) && pid(pw)) {
			++valid2;
		}
	};
	while (getline(cin, line)) {
		ss << " " << line << " ";
		if (line.empty()) check();
	}
	check();
	cout << valid1 << endl;
	cout << valid2 << endl;
	return 0;
}
