#include <vector>
#include <set>
#include <utility>
#include <functional>
#include <algorithm>

using CHT_TYPE = ll;
class ConvexHullTrickDynamic {
private:
	// ���� **************************************************************
	struct Line {
		CHT_TYPE a, b; // y = ax + b
		mutable std::function<const Line*()> getSuc; // ���̒����ւ̃|�C���^ (�\�[�g�ŗp����)

		bool operator<(const Line& rhs) const {
			// �擾�N�G���ł͎��̒����Ƃ̍����Ń\�[�g
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

			// �ʏ�̒����ǂ����͌X���\�[�g
			return a < rhs.a;
		}
	};

	// �����W�� **********************************************************
	class LinesSet : public std::multiset<Line> {
	private:
		// true -> �ŏ��l�N�G��, false -> �ő�l�N�G��
		bool flagMin;

	public:
		// �R���X�g���N�^ ( ������false�ōő�l�N�G��,�f�t�H���g�ōŏ��l�N�G�� )
		LinesSet(bool flagMin = true) : flagMin(flagMin) {};

		// ����l���s�K�v�ł��邩�ǂ���
		inline bool isBad(iterator l) {
			const auto&& nel = std::next(l);
			if (l == begin()) { // l���X���ŏ��̂Ƃ�
				if (nel == end()) return false; // l�����Ȃ��Ȃ�K�v
				return l->a == nel->a && l->b <= nel->b;
			}
			else {
				const auto&& prl = std::prev(l);
				if (nel == end()) return l->a == prl->a && l->b <= prl->b;
				return (prl->b - l->b) * (nel->a - l->a) >= (nel->b - l->b) * (prl->a - l->a);
			}
		}

		// ����y=ax+b��ǉ�����
		inline void add(CHT_TYPE a, CHT_TYPE b) {
			if (flagMin) a = -a, b = -b;
			auto&& it = insert({a, b});
			it->getSuc = [=] { return (std::next(it) == end() ? nullptr : &*std::next(it)); };
			if (isBad(it)) { erase(it); return; }
			while (std::next(it) != end() && isBad(std::next(it))) erase(std::next(it));
			while (it != begin() && isBad(std::prev(it))) erase(std::prev(it));
		}

		// �����Q�̒���x�̎��ɍŏ�(�ő�)�ƂȂ�l��Ԃ�
		inline CHT_TYPE get(CHT_TYPE x) {
			auto&& l = *lower_bound(Line{x, IS_QUERY});
			if (flagMin) return -l.a * x - l.b;
			else return l.a * x + l.b;
		}
	};

	static const CHT_TYPE IS_QUERY = std::numeric_limits<CHT_TYPE>::lowest();
	LinesSet linesSet;

public:
	// �R���X�g���N�^ ( ������false�ōő�l�N�G��,�f�t�H���g�ōŏ��l�N�G�� )
	ConvexHullTrickDynamic(bool flagMin = true) : linesSet(flagMin) {}
	// ����y=ax+b��ǉ�����
	inline void add(CHT_TYPE a, CHT_TYPE b) { linesSet.add(a, b); }
	// ����x�̂Ƃ��̒����W���ł̍ŏ��l�����߂�
	inline CHT_TYPE get(CHT_TYPE x) { return linesSet.get(x); }
};