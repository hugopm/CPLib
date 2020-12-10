struct union_find {
	int size;
	std::vector<int> leader, weight;

	union_find(int ta) : size(ta), leader(ta), weight(ta, 1) {
		iota(leader.begin(), leader.end(), 0);
	}

	int find(int x) {
		if (leader[x] != x) {
			leader[x] = find(leader[x]);
		}
		return leader[x];
	}

	bool merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) {
			return false;
		}
		if (weight[a] < weight[b]) {
			std::swap(a, b);
		}
		leader[b] = a;
		weight[a] += weight[b];
		return true;
	}
};

