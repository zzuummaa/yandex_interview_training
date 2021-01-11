#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

using namespace std;

vector<vector<int>> twoSum(vector<int>& nums, int left, int target) {
	vector<vector<int>> res;
	int right = nums.size() - 1;
	while (left < right) {
		int sum = nums[left] + nums[right];
		if (sum > target) {
			right--;
		} else if (sum < target) {
			left++;
		} else {
			res.emplace_back();
			res.back().push_back(nums[left]);
			res.back().push_back(nums[right]);
			while (left < right) {
				if (nums[left] == nums[left + 1]) {
					left++;
				} else {
					break;
				}
			}
			while (left < right) {
				if (nums[right] == nums[right - 1]) {
					right--;
				} else {
					break;
				}
			}
			left++;
		}
	}
	return res;
}

vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); i++) {
		for (int j = i + 1; j < nums.size(); j++) {
			int sum = nums[i] + nums[j];
			auto sums = twoSum(nums, j + 1, target - sum);
			for (auto& it: sums) {
				it.insert(it.begin(), nums[i]);
				it.insert(it.begin(), nums[j]);
			}
			sums.erase(unique(sums.begin(), sums.end()), sums.end());
			if (!res.empty() && !sums.empty()) {
				if (res.back() == sums.front()) res.pop_back();
			}
			res.insert(res.end(), sums.begin(), sums.end());
		}
	}
	return res;
}

int main() {
	int n;
	cin >> n;

	vector<int> nums(n);
	for (int & num : nums) {
		cin >> num;
	}

	int target;
	cin >> target;

	auto res = fourSum(nums, target);

	for (auto& sums: res) {
		for (int num: sums) {
			cout << num << " ";
		}
		cout << endl;
	}
}
