#pragma once
#include <vector>

template<class node, node (*op)(node, node), node (*e)()>
class segtree {
public:
	segtree(std::vector<node> v) : _n(v.size()), log(0) {
		while ((1 << log) < _n) {
			++log;
		}

		size = (1 << log);
		data.assign(2*size, e());

		for (int i = 0; i < _n; ++i) {
			data[size+i] = v[i];
		}

		for (int i = size-1; i >= 1; --i) {
			update(i);
		}
	}

	segtree(int t = 0, node x = e()) : segtree(std::vector<node>(t, x)) { }

	node get(int pos) {
		return data[size+pos];
	}

	void set(int pos, node val) {
		pos += size;
		data[pos] = val;
		for (int h = 1; h <= log; ++h) {
			update(pos >> h);
		}
	}

	void refresh(int pos, node proposal) {
		set(pos, op(data[size+pos], proposal));
	}

	node query_semi_open(int left, int right) {
		left += size;
		right += size;
		node res_left = e(), res_right = e(); 

		while (left < right) {
			if (left & 1) {
				res_left = op(res_left, data[left++]);
			}
			if (right & 1) {
				res_right = op(data[--right], res_right);
			}
			left >>= 1, right >>= 1;	
		}

		return op(res_left, res_right);
	}

	node query_all() {
		return data[1];
	}

private:
	int _n, log, size;
	std::vector<node> data;

	void update(int k) {
		data[k] = op(data[k<<1], data[k<<1|1]);
	}
};
