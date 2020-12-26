#pragma once
#include <vector>

class sieve {
public:
	sieve (int up_to) : small_div(up_to + 1, 0) {
		for (int x = 2; x <= up_to; ++x) {
			if (small_div[x] == 0) {
				small_div[x] = x;
				for (int c = 2; c*x <= up_to; ++c) {
					if (small_div[c*x] == 0)
						small_div[c*x] = x;
				}
			}
		}
	}

	std::vector<std::pair<int, int>> factorize(int x) {
		std::vector<std::pair<int, int>> res;
		while (x > 1) {
			if (res.empty() || res.back().first != small_div[x]) {
				res.emplace_back(small_div[x], 0);
			}
			++res.back().second;
			x /= small_div[x];
		}
		return res;
	}

private:
	std::vector<int> small_div;
};
