#pragma once
#include <vector>
#include <numeric>

class dsu {
public:
	dsu(int _n) : leader(_n), weight(_n, 1) {
		iota(leader.begin(), leader.end(), 0);
	}

	int find(int x) {
		if (leader[x] != x) {
			leader[x] = find(leader[x]);
		}
		return leader[x];
	}

	bool same(int a, int b) {
		return find(a) == find(b);
	}

	bool merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b) {
			if (weight[a] < weight[b]) {
				std::swap(a, b);
			}
			leader[b] = a;
			weight[a] += weight[b];
		}
		return a == b;
	}

private:
	std::vector<int> leader, weight;
};

