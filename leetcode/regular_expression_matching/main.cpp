#include <iostream>
#include <string>

using namespace std;

bool isMatchInternal(string_view s, string_view p) {
	auto s_it = s.begin();
	for (auto p_it = p.begin(); p_it < p.end(); p_it++) {
		if (*p_it == '*') continue;

		bool is_last = (p_it + 1) == p.end();
		bool is_not_z = is_last;
		if (!is_last) is_not_z = *(p_it + 1) != '*';

		if (is_not_z) {
			if (s_it == s.end()) return false;

			if (*p_it == '.' || *p_it == *s_it) {
				s_it++;
				continue;
			} else {
				return false;
			}
		}

		if (*(p_it + 1) == '*') {
			char c = *p_it;
			auto p_it_2 = p_it + 2;

			if (c == '.' && p_it_2 == p.end()) return true;

			while (s_it != s.end()) {
				if (c != '.' && c != *s_it) break;
				bool is_match = isMatchInternal(
						s.substr(s_it - s.begin(), string::npos),
						p.substr(p_it_2 - p.begin(), string::npos)
				);
				if (is_match) return true;
				s_it++;
			}

		}
	}

	return s.end() - s_it == 0;
}

bool isMatch(string s, string p) {
	return isMatchInternal(s, p);
}

int main() {
	string s, p;
	cin >> s >> p;

	cout << boolalpha << isMatch(s, p);
}