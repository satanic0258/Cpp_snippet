// Description: 2進文字列Sを10進整数に変換する。O(|S|)。

ll toDecimal(const std::string& binary) {
	size_t n = binary.size();
	ll res = 0;
	for (size_t i = 0; i < binary.size(); ++i) {
		res += (binary[n - i - 1] - '0') << i;
	}
	return res;
}