#include <iostream>

int main() {
	int len;
	std::cin >> len;

	int units_begin = 0;
	int prev_num = 2;
	int seq_max_len = 0;

	for (int i = 0; i < len; ++i) {
		int num;
		std::cin >> num;

		if (prev_num == 1 && num != 1) {
			int cur_seq_len = i - units_begin;
			if (cur_seq_len > seq_max_len) seq_max_len = cur_seq_len;
		} else if (prev_num != 1 && num == 1) {
			units_begin = i;
		}

		prev_num = num;
	}

	if (prev_num == 1) {
		int cur_seq_len = len - units_begin;
		if (cur_seq_len > seq_max_len) seq_max_len = cur_seq_len;
	}

	std::cout << seq_max_len;
}