// Description: データ構造をマージする一般的なテクを用いて高速なUnionFindを実現する。マージO(logN)。

//Quick Find Weighted
class QuickFindWeighted {
private:
	std::vector<int> group;
	std::vector<std::vector<int>> items;
public:
	QuickFindWeighted(int size) {
		group.resize(size);
		items.resize(size);
		for (int i = 0; i < size; ++i) {
			group[i] = i;
			items[i].assign({ i });
		}
	}

	// i1の所属するグループとi2の所属するグループを統合する
	void merge(int i1, int i2) {
		if (group[i1] == group[i2]) return;
		if (items[group[i1]].size() < items[group[i2]].size()) {
			std::swap(i1, i2);
		}
		int g1 = group[i1], g2 = group[i2];
		for (int i : items[g2]) group[i] = g1;
		items[g1].insert(items[g1].end(), items[g2].begin(), items[g2].end());
		items[g2].clear();
		items[g2].shrink_to_fit();
	}

	// i1とi2が同じグループに所属しているか
	bool same(int i1, int i2) {
		return group[i1] == group[i2];
	}
};