#include <vector>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

template<typename T, typename = std::enable_if<std::is_destructible<T>::value, T>>
class Cache {
	typedef std::chrono::steady_clock clock;
	typedef std::pair<clock::time_point, size_t> timeout_pair;

	struct time_pair_less {
		bool operator()(const timeout_pair& x, const timeout_pair& y) const {
			return x.first < y.first;
		}
	};

	clock::duration timeout;
	std::priority_queue<timeout_pair, std::vector<timeout_pair>, time_pair_less> timeout_queue;
	std::unordered_map<size_t, std::pair<T, clock::time_point>> element_map;

public:
	template<typename duration>
	explicit Cache(const duration& timeout) : timeout(std::chrono::duration_cast<clock::duration>(timeout)) {}

	void remove_expires(const clock::time_point& current_time = clock::now()) {
		while (!timeout_queue.empty()) {
			auto next = timeout_queue.top();
			if (next.first > current_time) break;
			timeout_queue.pop();

			auto element = element_map.find(next.second);
			if (element == element_map.end()) throw std::runtime_error("unexpected key missing in element_map");

			if (element->second.second > current_time) {
				timeout_queue.push(std::move(
					std::make_pair(element->second.second, element->first)
				));
			} else {
				element_map.erase(element);
			}
		}
	}

	void put(size_t key, T&& val) {
		auto expire_time = clock::now();
		remove_expires(expire_time);
		expire_time += timeout;

		auto element_val = std::make_pair(val, expire_time);

		auto it = element_map.find(key);
		if (it == element_map.end()) {
			element_map.insert(std::move(
				std::make_pair(key, std::move(element_val))
			));

			timeout_queue.push(std::move(
				std::make_pair(expire_time, key)
			));
		} else {
			it->second = std::move(element_val);
		}
	}

	std::pair<T, bool> get(size_t key) const {
		const auto it = element_map.find(key);
		if (it == element_map.end()) {
			return std::make_pair(T(), false);
		}
		return std::make_pair(it->second.first, true);
	}

	size_t size() const {
		return element_map.size();
	}
};

int main() {
	Cache<std::string> cache(std::chrono::microseconds(1));

	std::default_random_engine random_engine;
	std::uniform_int_distribution<int> idx_generator(0, 1000 * 1000);
	std::uniform_int_distribution<int> delay_generator(0, 1000);

	long long sum_len = 0;
	int it_count = 10 * 1000 * 1000;
	for (int i = 0; i < it_count; ++i) {
		cache.put(idx_generator(random_engine), "defergrdthgaaghtrefaghdsdthhhhdrhrdaw");
		sum_len += cache.size();
		std::this_thread::sleep_for(std::chrono::nanoseconds(delay_generator(random_engine)));
	}

	std::cout << "average len: " << (sum_len / it_count);
}

