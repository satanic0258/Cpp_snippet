// Description: 巨大数のmodを計算する。O(log|S|)。

int bigMod(const std::string& nStr, int mod) {
	int sz = nStr.size();
	ll res = 0;
	for (int i = 0; i < sz; ++i) {
		res = 10 * res + nStr[i++] - '0';
		if (i < sz) res = 10 * res + nStr[i] - '0';
		res %= mod;
	}
	return res;
}