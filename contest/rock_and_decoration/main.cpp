#include <string>
#include <set>
#include <iostream>

int main() {
	std::string j, s;
	std::cin >> j >> s;

	std::set<char> j_set(std::begin(j), std::end(j));
	int count = 0;
	for(char c: s) {
		if (j_set.find(c) != std::end(j_set)) count++;
	}
	std::cout << count;
}