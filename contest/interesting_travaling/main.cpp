#include <iostream>
#include <map>
#include <vector>

struct Coordinate {
	long x;
	long y;

	long dist(Coordinate& other) const {
		return labs(this->x - other.x) + labs(this->y - other.y);
	}
};

int main() {
	int city_count;
	std::cin >> city_count;

	std::vector<Coordinate> city_coordinates(city_count);
	for (int i = 0; i < city_count; ++i) {
		Coordinate c;
		std::cin >> c.x >> c.y;
		city_coordinates[i] = c;
	}

	long max_dist;
	std::cin >> max_dist;

	int begin_city_idx, end_city_idx;
	std::cin >> begin_city_idx >> end_city_idx;
	begin_city_idx--; end_city_idx--;

	std::vector<std::vector<int>> adjacency_list(city_coordinates.size());
	for (int i = 0; i < city_coordinates.size(); ++i) {
		for (int j = 0; j < city_coordinates.size(); ++j) {
			if (i == j) continue;
			if (city_coordinates[i].dist(city_coordinates[j]) <= max_dist) adjacency_list[i].push_back(j);
		}
	}

	std::vector<bool> visited_cities(city_coordinates.size(), false);
	visited_cities[begin_city_idx] = true;

	int search_depth = 0;

	std::vector<int> prev_cities(city_coordinates.size(), INT32_MAX);

	std::vector<int> suitable_city_idxs;
	std::vector<int> suitable_city_idxs_next;
	suitable_city_idxs.push_back(begin_city_idx);

	int min_cities = -1;
	do {
		search_depth++;
		for (auto i: suitable_city_idxs) {
			for (int adjacent = 0; adjacent < city_count; adjacent++) {
				if (i == adjacent) continue;
				if (city_coordinates[i].dist(city_coordinates[adjacent]) > max_dist) continue;

				if (visited_cities[adjacent]) continue;

				visited_cities[adjacent] = true;
				prev_cities[adjacent] = i;

				if (adjacent == end_city_idx) {
					min_cities = search_depth;
					suitable_city_idxs_next.clear();
					break;
				}

				suitable_city_idxs_next.push_back(adjacent);
			}
		}
		suitable_city_idxs.clear();
		suitable_city_idxs.swap(suitable_city_idxs_next);
	} while (!suitable_city_idxs.empty());

	std::cout << min_cities;
}