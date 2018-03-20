// Description: Trie木ライブラリ。

struct Trie {
	std::vector<std::map<char, int>> g;
	int p;

	Trie() : p(0) {
		g.emplace_back();
		++p;
	}

	// trieに文字列sを追加する
	void add(const std::string& s) {
		size_t par = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			if (g[par].find(s[i]) == g[par].end()) {
				g.emplace_back();
				g[par][s[i]] = p++;
			}
			par = g[par][s[i]];
		}
	}

	// 今見ている頂点から次の文字を検索する(なければ-1)
	int next(size_t par, char c) {
		if (g[par].find(c) == g[par].end()) return -1;
		return g[par][c];
	}

	// sがTrieのprefixか判定する
	bool find(const std::string& s) {
		int p = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			p = next(p, s[i]);
			if (p == -1) return false;
		}
		return true;
	}
};