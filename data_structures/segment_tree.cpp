template<typename st_node>
struct segment_tree {
	int size = 0;
	std::vector<st_node> array;

	segment_tree(std::vector<st_node> v) {
		size = v.size();
		array.resize(2*size);
		for (int idx = size; idx < 2*size; ++idx) {
			array[idx] = v[idx-size];
		}
		for (int idx = size-1; idx >= 1; --idx) {
			array[idx] = st_node::op(array[2*idx], array[2*idx+1]);
		}
	}

	segment_tree(int t, st_node x) :
		segment_tree(std::vector<st_node>(t, x)) { }

	void set(int idx, st_node val) {
		idx += size;
		array[idx] = val;
		while (idx > 1) {
			idx /= 2;
			array[idx] = st_node::op(array[2*idx], array[2*idx+1]);
		}
	}

	void refresh(int idx, st_node proposal) {
		upd(idx, st_node::op(array[idx+size], proposal));
	}

	st_node query(int left, int right) {
		left += size;
		right += size;
		st_node res; 
		while (left < right) {
			if (left & 1) {
				res = st_node::op(res, array[left++]);
			}
			if (right & 1) {
				res = st_node::op(res, array[--right]);
			}
			left /= 2; right /= 2;	
		}
		return res;
	}
};

