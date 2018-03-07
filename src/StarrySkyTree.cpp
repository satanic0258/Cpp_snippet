// Description: [a,b)への一様加算、[a,b)での最大(小)値クエリを達成する。加算O(logN)、最大(小)値クエリO(logN)。

// write [ StarrySkyTree<> sst(n) ] when using this snippet.
template<typename T = ll, bool QUERY_IS_GETMAX = true>
struct StarrySkyTree {
	std::vector<T> seg, lazy;
	int size;
	T inf;
	std::function<T(T&, T&)> func;
	StarrySkyTree() {}
	StarrySkyTree(int n) : inf((QUERY_IS_GETMAX ? std::numeric_limits<T>::min() : std::numeric_limits<T>::max())), func([](T& a, T& b) {return (QUERY_IS_GETMAX ? std::max(a, b) : std::min(a, b)); }) {
		init(n);
	}
	void init(int n) {
		size = 1;
		while (size < n) size *= 2;
		seg.resize(size * 2);
		lazy.resize(size * 2);
	}
	void push(int k, int l, int r) {
		seg[k] += lazy[k];
		if (r - l > 1) {
			lazy[k * 2 + 1] += lazy[k];
			lazy[k * 2 + 2] += lazy[k];
		}
		lazy[k] = 0;
	}
	void update(int a, int b, T v, int k, int l, int r) {
		push(k, l, r);
		if (r <= a || b <= l) return;
		if (a <= l && r <= b) {
			lazy[k] += v;
			push(k, l, r);
		}
		else {
			update(a, b, v, k * 2 + 1, l, (l + r) / 2);
			update(a, b, v, k * 2 + 2, (l + r) / 2, r);
			seg[k] = func(seg[k * 2 + 1], seg[k * 2 + 2]);

		}
	}
	// add v to [a,b)
	void update(int a, int b, T v) {
		update(a, b, v, 0, 0, size);
	}
	T query(int a, int b, int k, int l, int r) {
		push(k, l, r);
		if (r <= a || b <= l) return inf;
		if (a <= l && r <= b) return seg[k];
		T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return func(vl, vr);
	}
	// return min(or max) in [a,b)
	T query(int a, int b) {
		return query(a, b, 0, 0, size);
	}
};