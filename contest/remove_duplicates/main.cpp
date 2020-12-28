#include <iostream>
#include <set>

int main() {
	std::set<int> unique_elements;
	int len;
	std::cin >> len;

	for (int i = 0; i < len; ++i) {
		int element;
		std::cin >> element;
		unique_elements.insert(element);
	}

	for (auto it: unique_elements) {
		std::cout << it << std::endl;
	}
}