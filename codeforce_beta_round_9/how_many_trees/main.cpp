// http://codeforces.com/contest/9/problem/D

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

const int MAX_N = 35;

void assign_sum(std::vector<uint64_t>& a, const std::vector<uint64_t>& b) {
	for (int i = 0; i < std::min(a.size(), b.size()); i++) {
		a[i] += b[i];
	}
}

void composition(std::vector<uint64_t>& v, const std::vector<uint64_t>& va, const std::vector<uint64_t>& vb) {
	for (int i = 0; i < v.size(); i++) {
		if (va.size() > i) {
			v[i] += va[i] * std::accumulate(vb.begin(), vb.begin() + std::min<size_t>(i + 1, vb.size()), 0ull);
		} else if (vb.size() > i) {
			v[i] += vb[i] * std::accumulate(va.begin(), va.begin() + std::min<size_t>(i + 1, va.size()), 0ull);
		}
	}
}

int main() {
	int n, h;
	std::cin >> n >> h;

	std::vector<std::vector<uint64_t>> count_by_n_h(MAX_N + 1);

	count_by_n_h[0].push_back(1);

//	count_by_n_h[1].push_back(0);
//	count_by_n_h[1].push_back(1);

//	count_by_n_h[2].push_back(0);
//	count_by_n_h[2].push_back(0);
//	count_by_n_h[2].push_back(2);
//
//	count_by_n_h[3].push_back(0);
//	count_by_n_h[3].push_back(0);
//	count_by_n_h[3].push_back(1);
//	count_by_n_h[3].push_back(4);

	std::vector<uint64_t> count_by_h(n);
	for (int i = 1; i <= n; ++i) {
		count_by_h.resize(i+1);
		std::fill(count_by_h.begin(), count_by_h.end(), 0);
		for (int j = 0; j < i; j++) {
			composition(count_by_h, count_by_n_h[j], count_by_n_h[i - (j + 1)]);
//			assign_sum(count_by_h, count_by_n_h[j]);
//			assign_sum(count_by_h, count_by_n_h[i - (j + 1)]);
		}
		std::rotate(count_by_h.rbegin(), count_by_h.rbegin() + 1, count_by_h.rend());
		count_by_n_h[i] = count_by_h;
	}

	const auto& vec = count_by_n_h[n];
	std::cout << std::accumulate(vec.begin() + h, vec.end(), 0ull);
}