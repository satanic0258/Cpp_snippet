#include <vector>
#include <set>
#include <utility>
#include <functional>
#include <algorithm>

template<typename T>
class ConvecHullTrick {
private:
	// 直線群(配列)
	std::vector<std::pair<T, T>> linesVec;
	// 直線群(二分木)
	std::set<std::pair<T, T>> linesSet;
	// 追加する直線の傾きが単調であるか
	bool isMonotonicAddition;
	// 最小値(最大値)を求めるxが単調であるか
	bool isMonotonicX;
	// 最小/最大を判断する関数
	std::function<bool(T l, T r)> comp;

public:
	// コンストラクタ ( クエリが単調であった場合はflag = trueとする )
	ConvecHullTrick(bool flagX = false, bool flagAdd = false, std::function<bool(T l, T r)> compFunc = [](T l, T r) {return l >= r; })
		:isMonotonicX(flagX), isMonotonicAddition(flagAdd), comp(compFunc)  {
		linesVec.emplace_back(0, 0);
		linesSet.insert(std::make_pair(0, 0));
	};

	// 直線l1, l2, l3のうちl2が不必要であるかどうか
	bool check(std::pair<T, T> l1, std::pair<T, T> l2, std::pair<T, T> l3) {
		if (l1 < l3) std::swap(l1, l3);
		return (l3.second - l2.second) * (l2.first - l1.first) >= (l2.second - l1.second) * (l3.first - l2.first);
	}

	// 直線y=ax+bを追加する
	void add(T a, T b) {
		std::pair<T, T> line(a, b);
		if (isMonotonicAddition) {
			while (linesVec.size() >= 2 && check(*(linesVec.end() - 2), linesVec.back(), line))
				linesVec.pop_back();
			linesVec.emplace_back(line);
		}
		else {
			auto it = linesSet.insert(line).first;
			if (it != linesSet.begin() && std::next(it) != linesSet.end() && check(*std::prev(it), line, *std::next(it))) {
				linesSet.erase(it);
				return;
			}
			// 右の直線の削除
			if (it != linesSet.begin()) {
				auto it_r = std::prev(it);
				while (it_r != linesSet.begin() && check(*std::prev(it_r), *it_r, line)) {
					--it_r;
				}
				linesSet.erase(++it_r, it);
				it = linesSet.find(line);
			}
			// 左の直線の削除
			auto it_l = std::next(it);
			//while (it_l != linesSet.end() && std::next(it_l) != linesSet.end() && check(line, *it_l, *std::next(it_l))) {
			while (it_l != linesSet.end() && std::next(it_l) != linesSet.end() && check(*std::next(it_l), *it_l, line)) {
				++it_l;
			}
			linesSet.erase(++it, it_l);
			it = linesSet.find(line);
		}
	}

	// i番目の直線f_i(x)に対するxの時の値を返す
	T f(int i, T x) {
		return linesVec[i].first * x + linesVec[i].second;
	}

	// i番目の直線f_i(x)に対するxの時の値を返す
	T f(std::pair<T, T> line, T x) {
		return line.first * x + line.second;
	}

	// 直線群の中でxの時に最小(最大)となる値を返す
	T get(T x) {
		// 追加する直線の傾きが単調
		if (isMonotonicAddition) {
			// 最小値(最大値)クエリにおけるxが単調
			if (isMonotonicX) {
				static int head = 0;
				while (linesVec.size() - head >= 2 && comp(f(head, x), f(head + 1, x)))
					++head;
				return f(head, x);
			}
			else {
				int low = -1, high = linesVec.size() - 1;
				while (high - low > 1) {
					int mid = (high + low) / 2;
					(comp(f(mid, x), f(mid + 1, x)) ? low : high) = mid;
				}
				return f(high, x);
			}
		}
		else {
				int low = -1, high = linesSet.size() - 1;
				while (high - low > 1) {
					int mid = (high + low) / 2;
					(comp(f(*std::next(linesSet.begin(), mid), x), f(*std::next(linesSet.begin(), mid+1), x)) ? low : high) = mid;
				}
				return f(*std::next(linesSet.begin(), high), x);
				
				// ↑ちゃんと動くがO(N)
				// ↓要修正
				/*
				auto l = linesSet.begin(), r = linesSet.end(); --r;
				for (int i = 0; i < linesSet.size(); ++i) {
					T mid1 = (l->first + l->first + r->first) / 3;
					T mid2 = (l->first + r->first + r->first) / 3;
					auto m1 = linesSet.lower_bound(std::make_pair(mid1, 0));
					auto m2 = linesSet.lower_bound(std::make_pair(mid2, 0));
					if (comp(f(*m1, x), f(*m2, x))) l = m1;
					else r = m2;
				}
				auto res = (comp(f(*l, x), f(*r, x)) ? r : l);
				return (std::fabs(f(*res, x))!=INFINT) ? f(*res, x) : 0;
				*/
		}
	}
};