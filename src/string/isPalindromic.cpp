// Description: 与えられた文字列Sが回文かどうか判定する。O(|S|/2)。

bool isPalindromic(const std::string& s) {
	size_t sn = s.size();
	size_t n = sn / 2;
	for (size_t i = 0; i < n; ++i) {
		if (s[i] != s[sn - i - 1]) return false;
	}
	return true;
}