// Description: セグメント木を用いて区間内の最大値/最小値/合計を計算する。O(logN)。

// ------------>8------------ SegmentTree ------------>8------------

// -- Query Type enum.
enum QUERY { SUM, MAX, MIN };
template <class T = int>
class SegmentTree {
private:
	int ARY_SIZE;
	T init_val;
	std::vector<T> ary;
	std::function<T(T, T)> func;
public:
	SegmentTree(int n, QUERY qtype) : ARY_SIZE(1) { init(n, qtype); }
	SegmentTree(int n, T init_val, QUERY qtype) : ARY_SIZE(1) { init(n, init_val, qtype); }
	void init(int n, QUERY qtype) {
		T init_val;
		switch (qtype) {
		case SUM: init_val = 0; break;
		case MAX: init_val = std::numeric_limits<T>::lowest(); break;
		case MIN: init_val = std::numeric_limits<T>::max(); break;
		default: struct INVALID_QUERY_TYPE_ERROR {}; throw INVALID_QUERY_TYPE_ERROR(); break;
		}
		init(n, init_val, qtype);
	}
	void init(int n, T init_val, QUERY qtype) {
		std::function<T(T, T)> f;
		switch (qtype) {
		case SUM: f = [](T l, T r) {return l + r; }; break;
		case MAX: f = [](T l, T r) {return std::max(l, r); }; break;
		case MIN: f = [](T l, T r) {return std::min(l, r); }; break;
		default: struct INVALID_QUERY_TYPE_ERROR {}; throw INVALID_QUERY_TYPE_ERROR(); break;
		}
		init(n, init_val, f);
	}
	void init(int n, T init_val, std::function<T(T, T)> f) {
		while (ARY_SIZE < n) ARY_SIZE <<= 1;
		ARY_SIZE = ARY_SIZE * 2 - 1;
		ary.resize(ARY_SIZE, init_val);
		this->init_val = init_val;
		func = f;
	}
	// -- a[i] = val;
	void update(int i, T val) {
		i += ARY_SIZE / 2;
		ary[i] = val;
		while (i > 0) {
			i = (i - 1) / 2;
			ary[i] = func(ary[2 * i + 1], ary[2 * i + 2]);
		}
	}
	// -- a[i] += val;
	void add(int i, T val) {
		i += ARY_SIZE / 2;
		ary[i] += val;
		while (i > 0) {
			i = (i - 1) / 2;
			ary[i] = func(ary[2 * i + 1], ary[2 * i + 2]);
		}
	}
	// -- 区間[a, b)のfuncの返す値を返す (query_(a, b, 0, 0, n)と呼び出す)
	T query_(int a, int b, int i, int l, int r) {
		if (r <= a || b <= l) return init_val;
		if (a <= l && r <= b) return ary[i];
		else {
			T vl = query_(a, b, 2 * i + 1, l, (l + r) / 2);
			T vr = query_(a, b, 2 * i + 2, (l + r) / 2, r);
			return func(vl, vr);
		}
	}
	// -- [a, b)
	T query(int a, int b) { return query_(a, b, 0, 0, ARY_SIZE / 2 + 1); }
	T operator[](int i) { return ary[i + ARY_SIZE / 2]; }

	void debug_show() {
		for (int i = ARY_SIZE / 2; i < ARY_SIZE; ++i) std::cerr << ary[i] << " ";
		std::cerr << "\n";
	}
};
using ST = SegmentTree<int>;
// ------------8<------------ SegmentTree ------------8<------------