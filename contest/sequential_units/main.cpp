#include <iostream>

int main() {
	int len;
	std::cin >> len;

	int count = 0;
	int max_count = 0;

	for (int i = 0; i < len; ++i) {
		int num;
		std::cin >> num;

		if (num == 1) {
		 	count++;
		 	if (count > max_count) max_count = count;
		} else {
			count = 0;
		}
	}

	std::cout << max_count;
}