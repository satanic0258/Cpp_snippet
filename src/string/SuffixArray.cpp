// Description: SuffixArrayとLCPArrayを構築する．SuffixArrayO(|S|(log|S|)^2)，LCPArrayO(|S|)．

struct SuffixArray {
private:
	std::vector<int> tmp;
	int n, k;
public:
	std::string s;
	std::vector<int> rank, sa, lcp;
	SuffixArray() {}
	SuffixArray(const std::string& s) : n(s.size()), k(1), s(s), rank(s.size() + 1), sa(s.size() + 1), tmp(s.size() + 1), lcp(s.size() + 1) {
		constructSA();
		constructLCP();
	}

	bool compareSA(int i, int j) {
		if (rank[i] != rank[j]) return rank[i] < rank[j];
		int ri = i + k <= n ? rank[i + k] : -1;
		int rj = j + k <= n ? rank[j + k] : -1;
		return ri < rj;
	}

	void constructSA() {
		for (int i = 0; i <= n; ++i) {
			sa[i] = i;
			rank[i] = i < n ? s[i] : -1;
		}

		for (k = 1; k <= n; k *= 2) {
			std::sort(sa.begin(), sa.end(), [&](int i, int j) {return compareSA(i, j); });
			tmp[sa[0]] = 0;
			for (int i = 1; i <= n; ++i) {
				tmp[sa[i]] = tmp[sa[i - 1]] + compareSA(sa[i - 1], sa[i]);
			}
			for (int i = 0; i <= n; ++i) {
				rank[i] = tmp[i];
			}
		}
	}

	void constructLCP() {
		for (int i = 0; i <= n; ++i) rank[sa[i]] = i;

		int h = 0;
		lcp[0] = 0;
		for (int i = 0; i < n; ++i) {
			int j = sa[rank[i] - 1];
			if (h > 0) --h;
			for (; j + h < n && i + h < n; ++h) {
				if (s[j + h] != s[i + h]) break;
			}
			lcp[rank[i] - 1] = h;
		}
	}

	// Is T sub-string of S?  O(|T|log|S|)
	bool contain(const std::string& t) {
		int l = 0, r = s.size();
		while (r - l > 1) {
			int m = (l + r) / 2;
			// instead of [s.substr(sa[m], t.size()) < t]
			if (s.compare(sa[m], t.size(), t) < 0) l = m;
			else r = m;
		}
	}

	void debugShow() {
		std::cerr << "idx  " << " sa  " << "LCP  " << "suffix\n";
		for (int i = 0; i < n + 1; ++i) {
			std::cerr << std::setw(3) << std::setfill(' ') << i << "  ";
			std::cerr << std::setw(3) << std::setfill(' ') << sa[i] << "  ";
			std::cerr << std::setw(3) << std::setfill(' ') << lcp[i] << "  ";
			std::cerr << s.substr(sa[i]) << "\n";
		}
	}
};