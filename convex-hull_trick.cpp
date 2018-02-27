#include <vector>
#include <set>
#include <utility>
#include <functional>
#include <algorithm>

using CHT_TYPE = ll;
class ConvexHullTrickDynamic {
private:
	// 直線 **************************************************************
	struct Line {
		CHT_TYPE a, b; // y = ax + b
		mutable std::function<const Line*()> getSuc; // 次の直線へのポインタ (ソートで用いる)

		bool operator<(const Line& rhs) const {
			// 取得クエリでは次の直線との差分でソート
			if (rhs.b == IS_QUERY) {
				const Line* suc = getSuc();
				if (suc == nullptr) return false;
				const CHT_TYPE& x = rhs.a;
				return (suc->a - a)*x + suc->b - b > 0;
			}
			if (b == IS_QUERY) {
				const Line* suc = rhs.getSuc();
				if (suc == nullptr) return true;
				const CHT_TYPE& x = a;
				return (suc->a - rhs.a)*x + suc->b - rhs.b < 0;
			}

			// 通常の直線どうしは傾きソート
			return a < rhs.a;
		}
	};

	// 直線集合 **********************************************************
	class LinesSet : public std::multiset<Line> {
	private:
		// true -> 最小値クエリ, false -> 最大値クエリ
		bool flagMin;

	public:
		// コンストラクタ ( 第一引数falseで最大値クエリ,デフォルトで最小値クエリ )
		LinesSet(bool flagMin = true) : flagMin(flagMin) {};

		// 直線lが不必要であるかどうか
		inline bool isBad(iterator l) {
			const auto&& nel = std::next(l);
			if (l == begin()) { // lが傾き最小のとき
				if (nel == end()) return false; // lしかないなら必要
				return l->a == nel->a && l->b <= nel->b;
			}
			else {
				const auto&& prl = std::prev(l);
				if (nel == end()) return l->a == prl->a && l->b <= prl->b;
				return (prl->b - l->b) * (nel->a - l->a) >= (nel->b - l->b) * (prl->a - l->a);
			}
		}

		// 直線y=ax+bを追加する
		inline void add(CHT_TYPE a, CHT_TYPE b) {
			if (flagMin) a = -a, b = -b;
			auto&& it = insert({a, b});
			it->getSuc = [=] { return (std::next(it) == end() ? nullptr : &*std::next(it)); };
			if (isBad(it)) { erase(it); return; }
			while (std::next(it) != end() && isBad(std::next(it))) erase(std::next(it));
			while (it != begin() && isBad(std::prev(it))) erase(std::prev(it));
		}

		// 直線群の中でxの時に最小(最大)となる値を返す
		inline CHT_TYPE get(CHT_TYPE x) {
			auto&& l = *lower_bound(Line{x, IS_QUERY});
			if (flagMin) return -l.a * x - l.b;
			else return l.a * x + l.b;
		}
	};

	static const CHT_TYPE IS_QUERY = std::numeric_limits<CHT_TYPE>::lowest();
	LinesSet linesSet;

public:
	// コンストラクタ ( 第一引数falseで最大値クエリ,デフォルトで最小値クエリ )
	ConvexHullTrickDynamic(bool flagMin = true) : linesSet(flagMin) {}
	// 直線y=ax+bを追加する
	inline void add(CHT_TYPE a, CHT_TYPE b) { linesSet.add(a, b); }
	// あるxのときの直線集合での最小値を求める
	inline CHT_TYPE get(CHT_TYPE x) { return linesSet.get(x); }
};