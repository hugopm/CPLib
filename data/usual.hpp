#pragma once
#include "hl/data/segtree.hpp"
#include "hl/data/lazy_segtree.hpp"
#include <optional>
using ll = long long;

template<typename T, const T BIG_>
struct numeric_segtree {
	static constexpr T BIG = BIG_;
	static T fct_sum(T a, T b) { return a + b; }
	static T e_sum() { return 0; }

	static T fct_min(T a, T b) { return (a < b ? a : b); }
	static T e_min() { return BIG; }

	static T fct_max(T a, T b) { return (a > b ? a : b); }
	static T e_max() { return -BIG; }

	using segtree_min = segtree<T, fct_min, e_min>;
	using segtree_max = segtree<T, fct_max, e_max>;
	using segtree_sum = segtree<T, fct_sum, e_sum>;

	using lazy_min_add = lazy_segtree<T, fct_min, e_min, T, fct_sum, fct_sum, e_sum>;
	using lazy_max_add = lazy_segtree<T, fct_max, e_max, T, fct_sum, fct_sum, e_sum>;
	using lazy_sum_add = lazy_segtree<T, fct_sum, e_sum, T, fct_sum, fct_sum, e_sum>;

	using set_struct = std::optional<T>;
	static set_struct comp_set(set_struct f1, set_struct f2) {
		return (f1 ? f1 : f2);
	}
	static T eval_set(set_struct fct, T val) {
		return (fct ? *fct : val);
	}
	static set_struct e_set() {
		return std::nullopt;
	}

	using lazy_min_set = lazy_segtree<T, fct_min, e_min, set_struct, eval_set, comp_set, e_set>;
	using lazy_max_set = lazy_segtree<T, fct_max, e_max, set_struct, eval_set, comp_set, e_set>;
	using lazy_sum_set = lazy_segtree<T, fct_sum, e_sum, set_struct, eval_set, comp_set, e_set>;
};

using usual32 = numeric_segtree<int, (int)1e9>;
using usual64 = numeric_segtree<long long, (ll)3e18>;

