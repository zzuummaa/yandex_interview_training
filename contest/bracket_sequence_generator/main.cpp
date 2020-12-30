#include <iostream>
#include <string>

void print_sequences_internal(int init_num, std::string& seq, int open_bracket_count, int close_bracket_count) {
	if (init_num - seq.size() == 0) {
		if (open_bracket_count == close_bracket_count) {
			std::cout << seq << std::endl;
		}
		return;
	}

	if (open_bracket_count < init_num / 2) {
		seq.push_back('(');
		print_sequences_internal(init_num, seq, open_bracket_count+1, close_bracket_count);
		seq.pop_back();
	}

	if (open_bracket_count > close_bracket_count) {
		seq.push_back(')');
		print_sequences_internal(init_num, seq, open_bracket_count, close_bracket_count+1);
		seq.pop_back();
	}
}

void print_sequences(int count) {
	std::string seq;
	print_sequences_internal(count * 2, seq, 0, 0);
}

int main() {
	int count;
	std::cin >> count;

	print_sequences(count);
}