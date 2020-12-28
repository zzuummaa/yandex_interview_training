#include <iostream>
#include <map>

std::map<char, int> get_symbol_counts(const std::string& str) {
	std::map<char, int> symbol_counts;
	for (auto symbol: str) {
		auto it = symbol_counts.find(symbol);
		if (it != std::end(symbol_counts)) {
			it->second++;
		} else {
			symbol_counts.insert(std::make_pair(symbol, 1));
		}
	}
	return symbol_counts;
}

int main() {
	std::map<char, int> symbol_counts;

	std::string str1;
	std::string str2;

	std::cin >> str1 >> str2;

	std::cout << (get_symbol_counts(str1) == get_symbol_counts(str2));
}