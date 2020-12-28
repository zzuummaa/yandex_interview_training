#include <iostream>
#include <vector>
#include <set>

struct purse_info {
	bool is_in_purse;
	int real_coins;
	int all_coins;
	int idx;

	purse_info(): is_in_purse(false), real_coins(0), idx(0) {}
};

bool put_in_purses(std::vector<purse_info>& info, int coin_i, int count_count) {
	if (coin_i == info.size()) {
		int sum = 0;
		for (auto& it: info) sum += it.real_coins;
		return sum == count_count;
	}

	bool is_valid = put_in_purses(info, coin_i + 1, count_count);
	if (is_valid) return true;

	int default_idx = info[coin_i].idx;
	for (int i = default_idx; i < info.size(); i++) {
		if (i == coin_i) continue;
		if (info[i].is_in_purse || info[i].real_coins > info[coin_i].real_coins) continue;

		info[i].is_in_purse = true;
		info[coin_i].real_coins -= info[i].all_coins;
		info[coin_i].idx = i + 1;

		is_valid = put_in_purses(info, coin_i, count_count);
		if (is_valid) return true;

		info[i].is_in_purse = false;
		info[coin_i].real_coins += info[i].all_coins;
		info[coin_i].idx = default_idx;
	}

	return false;
}

bool is_valid(std::vector<int>& recursive_coins, int coin_count) {
	std::vector<purse_info> info(recursive_coins.size());
	for (int i = 0; i < info.size(); i++) {
		info[i].real_coins = recursive_coins[i];
		info[i].all_coins = recursive_coins[i];
	}
	std::vector<std::set<int>> purses(recursive_coins.size());
	return put_in_purses(info, 0, coin_count);
}

int main() {
	int n;
	std::cin >> n;

	std::vector<int> recursive_coins(n, 0);
	for (int i = 0; i < n; i++) std::cin >> recursive_coins[i];

	int m;
	std::cin >> m;

	std::cout << (is_valid(recursive_coins, m) ? "Yes" : "No");
}
