// Description: 遅延セグ木ライブラリ．区間更新,区間取得共にO(logN)．

// ------------>8---------- LazySegmentTree ---------->8------------

// ## write [ LST lst(n, SUM/MAX/MIN, ADD/UPD) ] when using this snippet.
enum QUERY_SEG_LazySegmentTree { SUM, MAX, MIN };
enum QUERY_LAZ_LazySegmentTree { ADD, UPD };
template<class SEG, class LAZ>
class LazySegmentTree {
private:
	std::vector<SEG> seg;
	std::vector<LAZ> laz;
	std::vector<bool> isUpdated;
	int ARY_SIZE;
	SEG eSeg;
	LAZ eLaz;
	std::function<SEG(SEG&, SEG&)> mergeSeg;
	std::function<LAZ(LAZ&, LAZ&)> mergeLaz;
	std::function<SEG(SEG&, LAZ&, int)> applyLaz;

	void push(int k, int l, int r) {
		if (!isUpdated[k]) {
			applyLaz(seg[k], laz[k], r - l);
			if (r - l > 1) {
				mergeLaz(laz[k * 2 + 1], laz[k]); isUpdated[k * 2 + 1] = false;
				mergeLaz(laz[k * 2 + 2], laz[k]); isUpdated[k * 2 + 2] = false;
			}
			isUpdated[k] = true;
			laz[k] = eLaz;
		}
	}
public:
	LazySegmentTree(int n, QUERY_SEG_LazySegmentTree qSeg, QUERY_LAZ_LazySegmentTree qLaz) : ARY_SIZE(1) {
		ARY_SIZE = 1;
		while (ARY_SIZE < n) ARY_SIZE *= 2;
		seg.resize(ARY_SIZE * 2 - 1);
		laz.resize(ARY_SIZE * 2 - 1);
		isUpdated.resize(ARY_SIZE * 2 - 1, true);

		switch (qSeg) {
			case SUM:
				eSeg = 0;
				mergeSeg = [](SEG& l, SEG& r) { return l + r; };
				break;
			case MAX:
				eSeg = std::numeric_limits<SEG>::lowest();
				mergeSeg = [](SEG& l, SEG& r) { return std::max(l, r); };
				break;
			case MIN:
				eSeg = std::numeric_limits<SEG>::max();
				mergeSeg = [](SEG& l, SEG& r) { return std::min(l, r); };
				break;
			default:
				struct INVALID_QUERY_TYPE_ERROR {};
				throw INVALID_QUERY_TYPE_ERROR();
				break;
		}

		switch (qLaz)
		{
			case ADD:
				eLaz = 0;
				mergeLaz = [](LAZ& l, LAZ& r) { return l += r; };
				if (qSeg == SUM) applyLaz = [](SEG& s, LAZ& l, int w) { return s += l * w; };
				else applyLaz = [](SEG& s, LAZ& l, int w) { return s += l; };
				break;
			case UPD:
				eLaz = 0;
				mergeLaz = [](LAZ& l, LAZ& r) { return l = r; };
				if (qSeg == SUM) applyLaz = [](SEG& s, LAZ& l, int w) { return s = l * w; };
				else applyLaz = [](SEG& s, LAZ& l, int w) { return s = l; };
				break;
			default:
				struct INVALID_QUERY_TYPE_ERROR {};
				throw INVALID_QUERY_TYPE_ERROR();
				break;
		}
	}
	void update(int a, int b, SEG v, int k, int l, int r) {
		push(k, l, r);
		if (r <= a || b <= l) return;
		if (a <= l && r <= b) {
			LAZ la(v);
			mergeLaz(laz[k], la);
			isUpdated[k] = false;
			push(k, l, r);
		}
		else {
			update(a, b, v, k * 2 + 1, l, (l + r) / 2);
			update(a, b, v, k * 2 + 2, (l + r) / 2, r);
			seg[k] = mergeSeg(seg[k * 2 + 1], seg[k * 2 + 2]);
		}
	}
	// ## update [l, r) with v
	void update(int l, int r, SEG v) {
		update(l, r, v, 0, 0, ARY_SIZE);
	}
	SEG query(int a, int b, int k, int l, int r) {
		push(k, l, r);
		if (r <= a || b <= l) return eSeg;
		if (a <= l && r <= b) return seg[k];
		SEG vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		SEG vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return mergeSeg(vl, vr);
	}
	// ## return SUM/MAX/MIN in [l, r)
	SEG query(int l, int r) {
		return query(l, r, 0, 0, ARY_SIZE);
	}
};

using LST = LazySegmentTree<ll, ll>;
// ------------>8---------- LazySegmentTree ---------->8------------