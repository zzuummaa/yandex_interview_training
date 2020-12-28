#include <iostream>
#include <set>
#include <cmath>

double f(int k) {
	double f_res = 3 * k;

	double digit_sum = 0;
	while (k >= 10) {
		digit_sum += k % (k / 10 * 10);
		k = k / 10;
	}
	digit_sum += k;

	f_res /= digit_sum * digit_sum;
	return f_res;
}

int main() {
	std::set<int> ns;
	int max_k = 1000 * 1000;
	for (int i = 1; i <= max_k; i++) {
		double res = f(i);
		if (std::abs(round(res) - res) < 10e-64) {
			ns.insert(static_cast<int>(res));
		}
	}

	int min_simple = 0;
	for (int i = 1; i < ns.size(); i++) {
		if (ns.find(i) == ns.end()) {
			min_simple = i;
			break;
		}
	}
	std::cout << min_simple;
}
