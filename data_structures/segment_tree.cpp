template<typename st_node>
struct segment_tree {
	int size = 0;
	vector<st_node> arr;

	segment_tree(vector<st_node> v) {
		size = v.size();
		arr.resize(2*size);
		for (int i = size; i < 2*size; ++i) {
			arr[i] = v[i-size];
		}
		for (int i = size-1; i >= 1; --i) {
			arr[i] = st_node::comb(arr[2*i], arr[2*i+1]);
		}
	}

	segment_tree(int t, st_node x) :
		segment_tree(vector<st_node>(t, x)) { }

	void set(int pos, st_node val) {
		pos += size;
		arr[pos] = val;
		while (pos > 1) {
			pos /= 2;
			arr[pos] = st_node::comb(arr[2*pos], arr[2*pos+1]);
		}
	}

	void refresh(int pos, st_node refr) {
		upd(pos, arr[pos+size].comb(refr));
	}

	st_node query(int left, int right) {
		left += size;
		right += size;
		st_node res; 
		while (left < right) {
			if (left & 1) {
				res = st_node::comb(res, arr[left++]);
			}
			if (right & 1) {
				res = st_node::comb(res, arr[--right]);
			}
			left /= 2; right /= 2;	
		}
		return res;
	}
};

