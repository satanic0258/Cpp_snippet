// Description: メンテナンス性を高めたセグ木。操作O(logN)。

// --------8<-------- ここを書き換える --------8<--------
struct Node {
	int v;
	Node() :v(0) {}
	Node(int v) :v(v) {}
	static Node merge(const Node& l, const Node& r);
};
Node Node::merge(const Node& l, const Node& r) {
	Node res;
	res = Node(l.v + r.v);
	return res;
};
// -------->8-------------------------------->8--------

//SegmentTreeEx(Node型セグ木)
class SegmentTreeEx {
public:
	int size;
	Node init_val;
	std::vector<Node> ary;

	SegmentTreeEx(int n, Node init_val) : size(1), init_val(init_val) {
		while (size < n) size *= 2;
		size = size * 2 - 1;
		ary.resize(size, init_val);
		init(0, 0, size / 2 + 1);
	}

	void init(int i, int l, int r) {
		if (r - l == 1) {
			// 葉ノードの初期化
			ary[i] = Node();
		}
		else {
			// 親ノードの初期化
			init(i * 2 + 1, l, (l + r) / 2);
			init(i * 2 + 2, (l + r) / 2, r);
			ary[i] = Node::merge(ary[i * 2 + 1], ary[i * 2 + 2]);
		}
	}

	void update(int i, Node node) {
		i += size / 2;
		// 葉ノードの更新
		// (加算等はここを書き換える : ary[i] += v;など)
		ary[i] = node;

		// 親ノードの更新
		while (i > 0) {
			i = (i - 1) / 2;
			ary[i] = Node::merge(ary[i * 2 + 1], ary[i * 2 + 2]);
		}
	}

	// 区間[a, b)の値を返す (query_(a, b, 0, 0, n)と呼び出す)
	Node query_(int a, int b, int i, int l, int r) const {
		if (r <= a || b <= l) return init_val;
		if (a <= l && r <= b) return ary[i];
		else {
			Node ln = query_(a, b, 2 * i + 1, l, (l + r) / 2);
			Node rn = query_(a, b, 2 * i + 2, (l + r) / 2, r);
			return Node::merge(ln, rn);
		}
	}

	// 区間[a, b)の値を返す
	Node query(int a, int b) const {
		return query_(a, b, 0, 0, size / 2 + 1);
	}
};