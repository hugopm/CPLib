#pragma once
#include <vector>

struct Sieve {
    std::vector<int> small_div;
    int lim_sieve;

    Sieve (int _n) : small_div(_n + 5, 0), lim_sieve(_n + 5) {
        for (int x = 2; x < lim_sieve; ++x) {
            if (small_div[x] == 0) {
                small_div[x] = x;
                for (int c = 2; c*x < lim_sieve; ++c) {
                    if (small_div[c*x] == 0)
                        small_div[c*x] = x;
                }
            }
        }
    }

    std::vector<std::pair<int, int>> factorize(int x) {
        std::vector<std::pair<int, int>> dcp;
        while (x > 1) {
            if (dcp.empty() || dcp.back().first != small_div[x]) {
                dcp.emplace_back(small_div[x], 0);
            }
            ++dcp.back().second;
            x /= small_div[x];
        }
        return dcp;
    }
};

