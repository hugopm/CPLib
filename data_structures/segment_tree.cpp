template<typename st_node>
struct segment_tree {
	int size = 0;
	std::vector<st_node> raw;

	segment_tree(std::vector<st_node> v) {
		size = v.size();
		raw.resize(2*size);
		for (int idx = size; idx < 2*size; ++idx) {
			raw[idx] = v[idx-size];
		}
		for (int idx = size-1; idx >= 1; --idx) {
			raw[idx] = st_node::op(raw[2*idx], raw[2*idx+1]);
		}
	}

	segment_tree(int t, st_node x) :
		segment_tree(std::vector<st_node>(t, x)) { }

	void set(int idx, st_node val) {
		idx += size;
		raw[idx] = val;
		while (idx > 1) {
			idx /= 2;
			raw[idx] = st_node::op(raw[2*idx], raw[2*idx+1]);
		}
	}

	void refresh(int idx, st_node proposal) {
		upd(idx, st_node::op(raw[idx+size], proposal));
	}

	st_node query(int left, int right) {
		left += size;
		right += size;
		st_node res; 
		while (left < right) {
			if (left & 1) {
				res = st_node::op(res, raw[left++]);
			}
			if (right & 1) {
				res = st_node::op(res, raw[--right]);
			}
			left /= 2; right /= 2;	
		}
		return res;
	}
};

