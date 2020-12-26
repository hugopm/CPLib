#pragma once
#include <vector>
#include <cassert>

template<class node,
node (*op)(node, node),
node (*e)(),
class fun,
node (*eval)(fun, node),
fun (*composition)(fun, fun),
fun (*id)()>
class lazy_segtree {
public:
	lazy_segtree(std::vector<node> v) : _n(v.size()), log(0) {
		while ((1 << log) < _n) {
			++log;
		}

		size = (1 << log);
		data.assign(2*size, e());
		lazy.assign(size, id());

		for (int i = 0; i < _n; ++i) {
			data[size + i] = v[i];
		}

		for (int i = size-1; i >= 1; --i) {
			update_one(i);
		}
	}

	lazy_segtree(int t = 0, node x = e()) : lazy_segtree(std::vector<node>(t, x)) { }

	node get(int pos) {
		int leaf = pos + size;
		push_anc(leaf);
		return data[leaf];
	}

	void set(int pos, node val) {
		int leaf = pos + size;
		push_anc(leaf);
		data[leaf] = val;
		update_anc(leaf);
	}

	node query_semi_open(int left, int right) {
		left += size;
		right += size;
		node res_left = e(), res_right = e();

		push_anc(left, left);
		push_anc(right, right);

		while (left < right) {
			if (left & 1) {
				res_left = op(res_left, data[left++]);
			}
			if (right & 1) {
				res_right = op(data[--right], res_right);
			}
			left >>= 1;
			right >>= 1;	
		}

		return op(res_left, res_right);
	}

	node query_all() {
		return data[1];
	}

	void apply_one(int pos, fun fct) {
		int leaf = pos + size;
		push_anc(leaf);
		data[leaf] = eval(fct, data[leaf]);
		update_anc(leaf);
	}

	void apply_semi_open(int left, int right, fun fct) {
		left += size;
		right += size;

		if (left == right) {
			return;
		}

		push_anc(left, left);
		push_anc(right - 1, right);

		int old_left = left, old_right = right;
		while (left < right) {
			if (left & 1) {
				all_apply(left++, fct);
			}
			if (right & 1) {
				all_apply(--right, fct);
			}
			left >>= 1;
			right >>= 1;
		}

		left = old_left, right = old_right;
		update_anc(left, left);
		update_anc(right - 1, right);
	}

private:
	int _n, log, size;
	std::vector<node> data;
	std::vector<fun> lazy;

	void update_one(int k) {
		data[k] = op(data[k << 1], data[k << 1 | 1]);
	}

	void update_anc(int leaf, int dev = 1) {
		int s = 1 + __builtin_ctz(dev);
		for (int i = s; i <= log; ++i) {
			update_one(leaf >> i);
		}
	}

	void all_apply(int k, fun fct) {
		data[k] = eval(fct, data[k]);
		if (k < size) {
			lazy[k] = composition(fct, lazy[k]);
		}
	}

	void push_one(int k) {
		all_apply(k << 1, lazy[k]);
		all_apply(k << 1 | 1, lazy[k]);
		lazy[k] = id();
	}

	void push_anc(int leaf, int dev = 1) {
		int s = 1 + __builtin_ctz(dev);
		for (int i = log; i >= s; --i) {
			push_one(leaf >> i);
		}
	}
};
