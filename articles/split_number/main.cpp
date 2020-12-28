#include <iostream>
#include <vector>
#include <algorithm>

struct SplitNumberOut {
	std::vector<uint64_t> cur_parts;
	std::vector<uint64_t> largest_parts;
};

bool split_number(const std::vector<uint32_t>& digits, int digit_i, SplitNumberOut& out) {
	if (digit_i >= digits.size()) {
		if (out.cur_parts.size() > out.largest_parts.size()) {
			out.largest_parts = out.cur_parts;
		}
		return true;
	}

	uint64_t number = 0;
	bool is_ok = false;

	for (int i = digit_i; i < digits.size(); i++) {
		if (number == 0 && digit_i - i > 0 && digits[i] == 0) return false;

		number = number * 10 + digits[i];

		if (std::find(out.cur_parts.begin(), out.cur_parts.end(), number) != out.cur_parts.end()) {
			continue;
		}
		out.cur_parts.push_back(number);

		if (split_number(digits, i + 1, out)) is_ok = true;

		out.cur_parts.pop_back();
	}

	return is_ok;
}

int main() {
	uint64_t n;
	std::cin >> n;

	std::vector<uint32_t> digits;
	while (n > 0) {
		digits.push_back(n % 10);
		n /= 10;
	}
	std::reverse(digits.begin(), digits.end());

	SplitNumberOut out;
	if (split_number(digits, 0, out)) {
		std::cout << out.largest_parts[0];
		for (int i = 1; i < out.largest_parts.size(); i++) {
			std::cout << "-" << out.largest_parts[i];
		}
	} else {
		std::cout << n;
	}
}