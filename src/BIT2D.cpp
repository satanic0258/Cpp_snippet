// Description: 2次元版BIT．add,sum共にO((log|H|)(log|W|))

struct BIT2D {
	int H, W;
	using TYPE = int;
	std::vector<std::vector<TYPE>> bit;
	BIT2D() : H(0), W(0) {}
	BIT2D(int h, int w) : H(h), W(w), bit(H + 1, std::vector<TYPE>(W + 1, 0)) {}
	BIT2D(int h, int w, TYPE init) : H(h), W(w), bit(H + 1, std::vector<TYPE>(W + 1, init)) {}

	// bit[y1][x1] += w;
	void add(int y1, int x1, TYPE w) {
		++y1; ++x1;
		for (int y = y1; y <= H ; y += y & -y) {
			for (int x = x1; x <= W ; x += x & -x) {
				bit[y][x] += w;
			}
		}
	}
	// return sum [0, 0] x (y1, x1);
	TYPE sum(int y1, int x1) {
		TYPE res = 0;
		for (int y = y1; y > 0; y -= y & -y) {
			for (int x = x1; x > 0; x -= x & -x) {
				res += bit[y][x];
			}
		}
		return res;
	}
	// return sum [y1, x1] x (y2, x2);
	TYPE sum(int y1, int x1, int y2, int x2) {
		return sum(y2, x2) - sum(y1, x2) - sum(y2, x1) + sum(y1, x1);
	}
	const std::vector<TYPE>& operator[](const int& i) const {
		return bit[i];
	}
};