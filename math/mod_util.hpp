#pragma once
#include <vector>
#include "hl/math/mod_int.hpp"

template<const int MOD>
class mod_util {
    private:
        using mint = mod_int<MOD>;
        std::vector<mint> fact, inv_raw, inv_fact;
        
    public:
        mod_util (int n) : fact(n + 1), inv_raw(n+1), inv_fact(n + 1) {
            fact[0].x = inv_fact[0].x = 1;
            inv_raw[1].x = fact[1].x = inv_fact[1].x = 1;
            for (int i = 2; i <= n; ++i) {
                inv_raw[i].x = MOD - (MOD/i) * inv_raw[MOD%i].x % MOD;
                fact[i] = fact[i-1].x * i;
                inv_fact[i] = inv_fact[i-1] * inv_raw[i];
            }
        }

        mint binom(int n, int k) {
            if (!(0 <= k && k <= n)) {
                return mint(0);
            }
            return fact[n] * inv_fact[k] * inv_fact[n-k];
        }

        mint fast_inv(int x) {
            if (0 <= x && x < (int)(inv_raw.size())) {
                return inv_raw[x];
            } else {
                return mint(x).inv();
            }
        }
};