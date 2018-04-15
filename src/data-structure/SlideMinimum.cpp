// Description: スライド最小値．minを取る区間が広義単調増加のとき使える．全体O(N)．

// ## Compare: min -> std::less<T>, max -> std::greater<T>
template<class T, class Compare>
class SlideMinimum {
private:
	std::deque<signed> deq;
	std::vector<T> a;
	Compare cmp;
	signed L, R;
public:
	SlideMinimum(const std::vector<T>& a) : a(a), cmp(Compare()), L(0), R(0) {}

	// ++L
	inline void incL() {
		if (deq.front() == L++) deq.pop_front();
	}
	// slide [L, R) to [l, R)
	inline void slideL(signed l) {
		while (L < l) incL();
	}
	// ++R
	inline void incR() {
		while (!deq.empty() && !cmp(a[deq.back()], a[R])) deq.pop_back();
		deq.push_back(R++);
	}
	// slide [L, R) to [L, r)
	inline void slideR(signed r) {
		while (R < r) incR();
	}
	// slide [L, R) to [l, r)
	inline void slide(signed l, signed r) {
		if (R <= l) {
			deq.clear();
			L = R = l;
		}
		slideR(r);
		slideL(l);
	}
	// reset deque ( slide [L, R) to [0, 0) )
	inline void clear() {
		deq.clear();
		L = R = 0;
	}
	inline signed getIndex() const {
		return deq.front();
	}
};