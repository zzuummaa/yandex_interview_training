#include <iostream>
#include <vector>

using namespace std;

// Получить k похожих на nums[idx] в отсортированном nums
vector<int> get_k(vector<int>& nums, int idx, int k) {
	vector<int> res;

	if (k > nums.size()) k = nums.size();
	if (idx >= nums.size() || idx < 0) return res;

	if (k > 0) {
		res.push_back(nums[idx]);
		k--;
	} else {
		return res;
	}

	int l = idx - 1;
	int r = idx + 1;
	for (;;) {
		if (k <= 0) return res;
		if (l >= 0 && r < nums.size()) {
			if (nums[idx] - nums[l] <  nums[r] - nums[idx]) {
				res.push_back(nums[l]);
				l--;
				k--;
			} else {
				res.push_back(nums[r]);
				r++;
				k--;
			}
		} else if (l < 0 && r < nums.size()) {
			res.push_back(nums[r]);
			r++;
			k--;
		} else if (l >= 0 && r >= nums.size()) {
			res.push_back(nums[l]);
			l--;
			k--;
		} else {
			return res;
		}
	}
}

int main() {
	int k, idx, n;
	cin >> k >> idx >> n;

	vector<int> nums(n);
	for (auto& num: nums) {
		cin >> num;
	}

	auto k_nums = get_k(nums, idx, k);
	for (auto num: k_nums) {
		cout << num << ' ';
	}
}