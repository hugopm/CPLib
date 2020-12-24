#pragma once
#include <vector>

template<class node, node (*op)(node, node), node (*id)()>
struct segment_tree {
	int size = 0;
	std::vector<node> raw;

	segment_tree(std::vector<node> v) {
		size = v.size();
		raw.resize(2*size);
		for (int i = size; i < 2*size; ++i) {
			raw[i] = v[i-size];
		}
		for (int i = size-1; i >= 1; --i) {
			raw[i] = op(raw[2*i], raw[2*i+1]);
		}
	}

	segment_tree(int t, node x = id()) :
		segment_tree(std::vector<node>(t, x)) { }

	void set(int i, node val) {
		i += size;
		raw[i] = val;
		while (i > 1) {
			i /= 2;
			raw[i] = op(raw[2*i], raw[2*i+1]);
		}
	}

	void refresh(int i, node proposal) {
		set(i, op(raw[i+size], proposal));
	}

	node query_semi_open(int left, int right) {
		left += size;
		right += size;
		node res = id(); 
		while (left < right) {
			if (left & 1) {
				res = op(res, raw[left++]);
			}
			if (right & 1) {
				res = op(res, raw[--right]);
			}
			left /= 2; right /= 2;	
		}
		return res;
	}

	node query_all() {
		return raw[1];
	}
};

