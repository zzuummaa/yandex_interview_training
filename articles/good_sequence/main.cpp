#include <iostream>
#include <vector>

struct Point {
	int x;
	int y;
	int z;

	static int dist(int x1, int y1, int x2, int y2) {
		int dx = x1 - x2;
		int dy = y1 - y2;
		return dx * dx + dy * dy;
	}

	int distOXY(const Point& other) const {
		return dist(x, y, other.x, other.y);
	}

	int distOYZ(const Point& other) const {
		return dist(y, z, other.y, other.z);
	}

	int distOXZ(const Point& other) const {
		return dist(x, z, other.x, other.z);
	}
};

bool is_good_sequence(const std::vector<Point>& points, const std::vector<int>& order, int permutation_count) {
	if (permutation_count % 2 == 0) return false;

	auto& first_p = points[order[0]];
	Point prev_dist{};
	Point is_trivial{ .x = 1, .y =  1, .z = 1};
	for (int i = 1; i < points.size(); i++) {
		int idx = order[i];

		int cur_dist = first_p.distOXY(points[idx]);
		is_trivial.x &= cur_dist >= prev_dist.x;
		prev_dist.x = cur_dist;

		cur_dist = first_p.distOYZ(points[idx]);
		is_trivial.y &= cur_dist >= prev_dist.y;
		prev_dist.y = cur_dist;

		cur_dist = first_p.distOXZ(points[idx]);
		is_trivial.z &= cur_dist >= prev_dist.z;
		prev_dist.z = cur_dist;
	}

	return !(is_trivial.x || is_trivial.y || is_trivial.z);
}

bool find_good_sequence(const std::vector<Point>& points, std::vector<int>& order, int order_idx, int permutation_count) {
	if (is_good_sequence(points, order, permutation_count)) return true;
	if (order_idx >= order.size()) return false;

	permutation_count++;
	for (int i = order_idx + 1; i < order.size(); i++) {
		std::swap(order[order_idx], order[i]);
		if (is_good_sequence(points, order, permutation_count)) return true;
		if (find_good_sequence(points, order, i + 1, permutation_count)) return true;
		std::swap(order[order_idx], order[i]);
	}

	return false;
}

int main() {
	int n;
	std::cin >> n;

	std::vector<Point> points(n);
	std::vector<int> order(n);
	for (int i = 0; i < n; i++) {
		order[i] = i;
		std::cin >> points[i].x >> points[i].y >> points[i].z;
	}

	if (find_good_sequence(points, order, 0, 0)) {
		for (auto it: order) {
			std::cout << (it + 1) << " ";
		}
	} else {
		std::cout << "Not found";
	}
}