#include <iostream>
#include <vector>
#include <chrono>

typedef std::vector<int>::iterator tree_iterator;

long long tree_count_internal(tree_iterator lbegin, tree_iterator lend, tree_iterator rbegin, tree_iterator rend) {
	if (lend == lbegin && rend == rbegin) return 1;

	long long lcount = lend - lbegin > 0 ? 0 : 1;
	for (auto it = lbegin; it < lend; it++) {
		lcount += tree_count_internal(lbegin, it, it + 1, lend);
	}

	long long rcount = rend - rbegin > 0 ? 0 : 1;
	for (auto it = rbegin; it < rend; it++) {
		rcount += tree_count_internal(rbegin, it, it + 1, rend);
	}

	return lcount * rcount;
}

long long tree_count(int n) {
	std::vector<int> unused;
	for (int i = 1; i <= n; ++i) unused.push_back(i);

	long long count = 0;
	for (auto it = unused.begin(); it < unused.end(); it++) {
		count += tree_count_internal(unused.begin(), it, it + 1, unused.end());
	}
	return count;
}

int main() {
	int n;
	std::cin >> n;

	auto start_time = std::chrono::high_resolution_clock::now();
	long long count = tree_count(n);
	auto end_time = std::chrono::high_resolution_clock::now();

	std::cout << count << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms.";
}