#include <iostream>
#include <vector>

using namespace std;

int seq_dig(vector<int>& nums) {
	int zero_i = nums[0] == 0 ? 0 : -1;
	int seq = nums[0] == 1 ? 1 : 0;
	int max_seq = seq;
	int seq_from_zero = 0;
	bool is_zero_rm = false;

	for (int i = 1; i < nums.size(); i++) {
		if (nums[i] == 0) {
			zero_i = i;
			if (i + 1 == nums.size()) continue;
			if (is_zero_rm) {
				if (nums[i - 1] == 1 && nums[i + 1] == 1) {
					seq = i - seq_from_zero;
					seq_from_zero = i + 1;
				} else {
					is_zero_rm = false;
					seq = 0;
				}
			} else {
				if (nums[i - 1] == 1 && nums[i + 1] == 1) {
					is_zero_rm = true;
					seq_from_zero = i + 1;
				} else {
					is_zero_rm = false;
					seq = 0;
				}
			}
		} else {
			seq++;
			if (seq > max_seq) max_seq = seq;
		}
	}

	return zero_i == -1 ? max_seq - 1 : max_seq;
}

int main() {
	int n;
	cin >> n;

	vector<int> nums(n);
	for (auto& it: nums) {
		cin >> it;
	}

	cout << seq_dig(nums);
}

