#include <iostream>
#include <vector>
#include <chrono>

int main() {
	int n;
	std::cin >> n;

	auto start_time = std::chrono::high_resolution_clock::now();

	std::vector<long long> count_by_n(n + 1, 0);
	count_by_n[0] = 1;

	for (int i = 1; i < count_by_n.size(); i++) {
		for (int c = 0; c < i; c++) {
			count_by_n[i] += count_by_n[c - 0] * count_by_n[i - (c + 1)];
		}
	}

	auto end_time = std::chrono::high_resolution_clock::now();

	std::cout << count_by_n[n] << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms.";
}