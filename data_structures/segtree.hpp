#pragma once
#include <vector>

template<class node, node (*op)(node, node), node (*e)()>
struct segtree {
	int log = 0, size = 0;
	std::vector<node> arr;

	segtree(std::vector<node> v) {
		int _n = v.size();
		log = 0;
		while ((1 << log) < _n) {
			++log;
		}

		size = (1 << log);
		arr.assign(2*size, e());

		for (int i = 0; i < _n; ++i) {
			arr[size+i] = v[i];
		}

		for (int i = size-1; i >= 1; --i) {
			arr[i] = op(arr[2*i], arr[2*i+1]);
		}
	}

	segtree(int t = 0, node x = e()) : segtree(std::vector<node>(t, x)) { }

	void set(int i, node val) {
		i += size;
		arr[i] = val;
		while (i > 1) {
			i /= 2;
			arr[i] = op(arr[2*i], arr[2*i+1]);
		}
	}

	void refresh(int i, node proposal) {
		set(i, op(arr[i+size], proposal));
	}

	node query_semi_open(int left, int right) {
		left += size;
		right += size;
		node res = e(); 
		while (left < right) {
			if (left & 1) {
				res = op(res, arr[left++]);
			}
			if (right & 1) {
				res = op(res, arr[--right]);
			}
			left >>= 1, right >>= 1;	
		}
		return res;
	}

	node query_all() {
		return arr[1];
	}
};

