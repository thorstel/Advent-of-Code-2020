#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<int Part>
static ll evaluate(string expr)
{
	static_assert(Part == 1 || Part == 2);

	string::size_type pos_closing;
	while ((pos_closing = expr.find(')')) != string::npos) {
		auto pos_opening = expr.rfind('(', pos_closing);
		assert(pos_opening != string::npos);
		auto sub_expr = expr.substr((pos_opening + 1), (pos_closing - pos_opening - 1));
		ll val = evaluate<Part>(sub_expr);
		expr.erase(pos_opening, (pos_closing - pos_opening + 1));
		expr.insert(pos_opening, to_string(val));
	}

	if (Part == 2) {
		string::size_type pos_mult;
		if ((pos_mult = expr.find('*')) != string::npos) {
			auto sub_expr1 = expr.substr(0, pos_mult);
			auto sub_expr2 = expr.substr((pos_mult + 1), expr.size());
			return evaluate<Part>(sub_expr1) * evaluate<Part>(sub_expr2);
		}
	}

	stringstream ss {expr};
	string op;
	ll value, other;
	ss >> value;
	while (ss >> op >> other) {
		if (op == "*") { value *= other; }
		else if (op == "+") { value += other; }
		else { assert(false); }
	}
	return value;
}

int main()
{
	ll sum1 = 0, sum2 = 0;
	string line;
	while (getline(cin, line)) {
		sum1 += evaluate<1>(line);
		sum2 += evaluate<2>(line);
	}
	cout << sum1 << endl;
	cout << sum2 << endl;
	return 0;
}
