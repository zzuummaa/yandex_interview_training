#include <iostream>
#include <map>
#include <vector>
#include <queue>

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

	std::vector<int> distances(city_coordinates.size(), -1);
	distances[begin_city_idx] = 0;

	std::queue<int> next_cities;
	next_cities.push(begin_city_idx);

	while (!next_cities.empty()) {
		int next = next_cities.front();
		next_cities.pop();

		for (int adj: adjacency_list[next]) {
			if (visited_cities[adj]) continue;

			visited_cities[adj] = true;
			distances[adj] = distances[next] + 1;
			next_cities.push(adj);
		}
	}

	std::cout << distances[end_city_idx];
}